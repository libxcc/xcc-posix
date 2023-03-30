#include <xcc-posix/json.h>
#include <xcc-posix/string.h>
#include <xcc-posix/stream.h>
#include <xcc-posix/memory.h>



#define X_JSON_TYPE_DOUBLE			(9)

// json data
struct x_json_data
{
	struct x_json_data*		prev;
	struct x_json_data*		next;
	struct x_json_data*		child;

	int 				type;
	char*				name;
	union
	{
		x_int64_t 		v_llong;
		double 		v_double;
		char*			v_string;
	}value;
};





// Skip extraneous characters from a string
static const char* __xcall__ x_json_format_skip(const char* _String)
{
	char 		vChar = 0;
	while(_String)
	{
		vChar = *_String;
		if(vChar == '\0')
		{
			return NULL;
		}
		if(vChar == '\r' || vChar == '\n' || vChar == '\t' || vChar == ' ')
		{
			++_String;
		}
		else
		{
			break;
		}
	}
	return _String;
}

// Check if a character is a number
static const char* __xcall__ x_json_format_check_number(const char* _String)
{
	char 		vChar = 0;
	while(_String)
	{
		vChar = _String[0];
		if('0' <= vChar && vChar <= '9')
		{
		}
		else
		{
			switch (vChar)
			{
				case ' ':
				case '.':
				case '+':
				case '-':
				case 'E':
				case 'e':
				case 'X':
				case 'x':
					break;
				default:
					return _String;
			}
		}
		++_String;
	}
	return _String;
}

// Format Json object from string
static const char* __xcall__ x_json_from_string(const char* _String, x_json_t* _Object)
{
	if(_String == NULL || _Object == NULL)
	{
		return NULL;
	}

	_String = x_json_format_skip(_String);
	if(_String == NULL)
	{
		return NULL;
	}

	char 		vChar = _String[0];
	if(0 == x_posix_strncmp(_String, "null", 4))
	{
		*_Object = x_json_new_null();
		return x_json_format_skip(_String + 4);
	}
	else if(0 == x_posix_strncmp(_String, "true", 4))
	{
		*_Object = x_json_new_boolean(true);
		return x_json_format_skip(_String + 4);
	}
	else if(0 == x_posix_strncmp(_String, "false", 5))
	{
		*_Object = x_json_new_boolean(false);
		return x_json_format_skip(_String + 5);
	}
	else if(vChar == '+' || vChar == '-' || ('0' <= vChar && vChar <= '9'))
	{
		const char*	vEnd = x_json_format_check_number(_String + 1);
		if(vEnd)
		{
			x_size_t 	vSize = vEnd - _String;
			char*		vBuffer = (char*) x_posix_malloc(vSize + 1);
			if(vBuffer)
			{
				x_posix_strncpy(vBuffer, _String, vSize);
				vBuffer[vSize] = 0;

				if(0 == x_posix_strncmp(vBuffer, "0x", 2))
				{
					// number hex
					x_uint64_t	vValue = x_posix_strtoull(vBuffer, NULL, 16);
					*_Object = x_json_new_number((x_int64_t)vValue);
				}
				else if(x_posix_stristr(vBuffer, "E") || x_posix_strstr(vBuffer, "."))
				{
					// number double
					double 	vValue = x_posix_strtod(vBuffer, NULL);
					*_Object = x_json_new_double(vValue);
				}
				else if('+' == vChar)
				{
					x_uint64_t	vValue = x_posix_strtoull(vBuffer + 1, NULL, 10);
					*_Object = x_json_new_number((x_int64_t)vValue);
				}
				else if('-' == vChar)
				{
					x_int64_t	vValue = x_posix_strtoll(vBuffer, NULL, 10);
					*_Object = x_json_new_number(vValue);
				}
				else
				{
					x_uint64_t	vValue = x_posix_strtoull(vBuffer, NULL, 10);
					*_Object = x_json_new_number((x_int64_t)vValue);
				}

				x_posix_free(vBuffer);
				return x_json_format_skip(_String + vSize);
			}
		}
	}
	else if(vChar == '\"')
	{
		const char*	vEnd = x_posix_strchr(_String + 1, '\"');
		if(vEnd)
		{
			x_size_t 	vSize = vEnd - _String - 1;
			if(vSize == 0)
			{
				*_Object = x_json_new_string(NULL);
				return x_json_format_skip(_String + vSize + 2);
			}
			else
			{
				char*	vBuffer = (char*) x_posix_malloc(vSize + 1);
				if(vBuffer)
				{
					x_posix_strncpy(vBuffer, _String + 1, vSize);
					vBuffer[vSize] = 0;
					*_Object = x_json_new_string(vBuffer);
					x_posix_free(vBuffer);
					return x_json_format_skip(_String + vSize + 2);
				}
			}
		}
	}
	else if(vChar == '[')
	{
		_String = x_json_format_skip(_String + 1);
		if(_String)
		{
			x_json_t 	vJsonArray = x_json_new_array();
			if(vJsonArray)
			{
				while(_String)
				{
					vChar = _String[0];
					if(vChar == ']')
					{
						*_Object = vJsonArray;
						return x_json_format_skip(_String + 1);
					}

					x_json_t	vArrayNode = NULL;
					_String = x_json_from_string(_String, &vArrayNode);
					if(vArrayNode == NULL)
					{
						_String = NULL;
						break;
					}
					x_json_array_append(vJsonArray, vArrayNode);

					_String = x_json_format_skip(_String);
					if(_String == NULL)
					{
						break;
					}

					// Check for commas
					if(_String[0] == ',')
					{
						++_String;
					}
					_String = x_json_format_skip(_String);
				}
				x_json_free(vJsonArray);
			}
		}
	}
	else if(vChar == '{')
	{
		_String = x_json_format_skip(_String + 1);
		if(_String)
		{
			x_json_t 	vJsonObject = x_json_new_object();
			if(vJsonObject)
			{
				while(_String)
				{
					vChar = _String[0];
					if(vChar == '}')
					{
						*_Object = vJsonObject;
						return x_json_format_skip(_String + 1);
					}

					// find key
					x_json_t	vObjectKey = NULL;
					_String = x_json_from_string(_String, &vObjectKey);
					if(vObjectKey == NULL)
					{
						_String = NULL;
						break;
					}
					if(vObjectKey->type != X_JSON_TYPE_STRING)
					{
						x_json_free(vObjectKey);
						_String = NULL;
						break;
					}

					// find split
					_String = x_json_format_skip(_String);
					if(_String == NULL || _String[0] != ':')
					{
						x_json_free(vObjectKey);
						_String = NULL;
						break;
					}
					++_String;

					// find value
					x_json_t	vObjectValue = NULL;
					_String = x_json_from_string(_String, &vObjectValue);
					if(vObjectValue == NULL)
					{
						x_json_free(vObjectKey);
						_String = NULL;
						break;
					}
					x_json_object_insert(vJsonObject, x_json_as_string(vObjectKey), vObjectValue);
					x_json_free(vObjectKey);
					_String = x_json_format_skip(_String);
					if(_String == NULL)
					{
						break;
					}

					// Check for commas
					if(_String[0] == ',')
					{
						++_String;
					}
					_String = x_json_format_skip(_String);
				}
				x_json_free(vJsonObject);
			}
		}
	}

	return NULL;
}

// Calculate the length required to convert an object to a string
static x_size_t __xcall__ x_json_to_string_size(x_json_t _Object, int _Format, x_size_t _Level)
{
	x_size_t	vSize = 0;
	switch (_Object->type)
	{
		case X_JSON_TYPE_NULL:
			vSize = 4;
			break;
		case X_JSON_TYPE_BOOLEAN:
			vSize = _Object->value.v_llong ? 4 : 5;
			break;
		case X_JSON_TYPE_NUMBER:
			vSize = x_posix_snprintf(NULL, 0, "%lld", _Object->value.v_llong);
			break;
		case X_JSON_TYPE_DOUBLE:
			vSize = x_posix_snprintf(NULL, 0, "%lf", _Object->value.v_double);
			break;
		case X_JSON_TYPE_STRING:
			vSize = x_posix_strlen(_Object->value.v_string) + 2;
			break;
		case X_JSON_TYPE_ARRAY:
		{
			// [
			vSize += 1;
			x_json_t 	vNode = _Object->child;
			while(vNode)
			{
				// \t * _Level + \n
				vSize += (_Format == X_JSON_FORMAT_TAB) ? (_Level + 1 + 1) : 0;

				// value
				vSize += x_json_to_string_size(vNode, _Format, _Level + 1);

				// ,
				vSize += vNode->next ? 1 : 0;

				vNode = vNode->next;
			}
			// \t * _Level + \n
			vSize += (_Format == X_JSON_FORMAT_TAB) ? (_Level + 1) : 0;
			// ]
			vSize += 1;
		}
			break;
		case X_JSON_TYPE_OBJECT:
		{
			// {
			vSize += 1;
			x_json_t 	vNode = _Object->child;
			while(vNode)
			{
				// \t * _Level + \n
				vSize += (_Format == X_JSON_FORMAT_TAB) ? (_Level + 1 + 1) : 0;

				// "name":
				vSize += x_posix_strlen(vNode->name) + 3;

				// value
				vSize += x_json_to_string_size(vNode, _Format, _Level + 1);

				// ,
				vSize += vNode->next ? 1 : 0;

				vNode = vNode->next;
			}
			// \t * _Level + \n
			vSize += (_Format == X_JSON_FORMAT_TAB) ? (_Level + 1) : 0;
			// {
			vSize += 1;
		}
			break;
		default:
			break;
	}
	return vSize;
}

// Json build format string
static x_size_t __xcall__ x_json_to_string_format(char* _String, int _Format, x_size_t _Level)
{
	x_size_t	vSize = 0;
	if(X_JSON_FORMAT_TAB == _Format)
	{
		_String[vSize] = '\n';
		for(vSize = 1; vSize <= _Level; ++vSize)
		{
			_String[vSize] = '\t';
		}
	}
	return vSize;
}

// Convert Json object to string
static x_size_t __xcall__ x_json_to_string(char* _String, x_json_t _Object, int _Format, x_size_t _Level)
{
	x_size_t	vSize = 0;
	switch (_Object->type)
	{
		case X_JSON_TYPE_NULL:
			x_posix_strcpy(_String, "null");
			vSize = 4;
			break;
		case X_JSON_TYPE_BOOLEAN:
			x_posix_strcpy(_String, _Object->value.v_llong ? "true" : "false");
			vSize = _Object->value.v_llong ? 4 : 5;
			break;
		case X_JSON_TYPE_NUMBER:
			vSize = x_posix_sprintf(_String, "%lld", _Object->value.v_llong);
			break;
		case X_JSON_TYPE_DOUBLE:
			vSize = x_posix_sprintf(_String, "%lf", (double)_Object->value.v_double);
			break;
		case X_JSON_TYPE_STRING:
			vSize = x_posix_sprintf(_String, "\"%s\"", _Object->value.v_string);
			break;
		case X_JSON_TYPE_ARRAY:
		{
			x_posix_strcpy(_String + vSize, "[");
			vSize += 1;

			x_json_t 	vNode = _Object->child;
			while(vNode)
			{
				vSize += x_json_to_string_format(_String + vSize, _Format, _Level + 1);

				vSize += x_json_to_string(_String + vSize, vNode, _Format, _Level + 1);

				if(vNode->next)
				{
					_String[vSize] = ',';
					vSize += 1;
				}

				vNode = vNode->next;
			}
			vSize += x_json_to_string_format(_String + vSize, _Format, _Level);

			x_posix_strcpy(_String + vSize, "]");
			vSize += 1;
		}
			break;
		case X_JSON_TYPE_OBJECT:
		{
			x_posix_strcpy(_String + vSize, "{");
			vSize += 1;

			x_json_t 	vNode = _Object->child;
			while(vNode)
			{
				vSize += x_json_to_string_format(_String + vSize, _Format, _Level + 1);

				vSize += x_posix_sprintf(_String + vSize, "\"%s\"", vNode->name);

				_String[vSize] = ':';
				vSize += 1;

				vSize += x_json_to_string(_String + vSize, vNode, _Format, _Level + 1);

				if(vNode->next)
				{
					_String[vSize] = ',';
					vSize += 1;
				}

				vNode = vNode->next;
			}
			vSize += x_json_to_string_format(_String + vSize, _Format, _Level);

			x_posix_strcpy(_String + vSize, "}");
			vSize += 1;
		}
			break;
		default:
			break;
	}
	return vSize;
}





// Parse String to Json
_XPOSIXAPI_ x_json_t __xcall__ x_json_parse(const char* _String)
{
	if(_String == NULL)
	{
		return NULL;
	}

	x_json_t	vJsonValue = NULL;

	x_json_from_string(_String, &vJsonValue);

	return vJsonValue;
}

// Format Json to string
_XPOSIXAPI_ char* __xcall__ x_json_print(x_json_t _Object)
{
	return x_json_printf(_Object, X_JSON_FORMAT_NULL);
}

// Format Json to string
_XPOSIXAPI_ char* __xcall__ x_json_printf(x_json_t _Object, int _Format)
{
	char*		vString = NULL;
	x_size_t	vAdvance = x_json_to_string_size(_Object, _Format, 0);
	x_size_t 	vActual = 0;
	if(vAdvance > 0)
	{
		vString = (char*) x_posix_malloc(vAdvance + 1);
		if(vString)
		{
			vString[vAdvance] = 0;

			vActual = x_json_to_string(vString, _Object, _Format, 0);
			if(vAdvance == vActual)
			{
				return vString;
			}
			x_posix_free(vString);
		}
	}
	return NULL;
}

// Clone a Json
_XPOSIXAPI_ x_json_t __xcall__ x_json_clone(x_json_t _Object)
{
	char*		vString = x_json_print(_Object);
	x_json_t	vClone = x_json_parse(vString);
	x_posix_free(vString);
	return vClone;
}





// Create an object of type null
_XPOSIXAPI_ x_json_t __xcall__ x_json_new_null()
{
	x_json_t	vObject = (x_json_t) x_posix_malloc(sizeof(struct x_json_data));
	if(vObject)
	{
		x_posix_memset(vObject, 0, sizeof(struct x_json_data));

		vObject->type = X_JSON_TYPE_NULL;
	}
	return vObject;
}

// Create an object of type boolean
_XPOSIXAPI_ x_json_t __xcall__ x_json_new_boolean(bool _Value)
{
	x_json_t	vObject = x_json_new_number(_Value ? 1 : 0);
	if(vObject)
	{
		vObject->type = X_JSON_TYPE_BOOLEAN;
	}
	return vObject;
}

// Create an object of type number
_XPOSIXAPI_ x_json_t __xcall__ x_json_new_number(x_int64_t _Value)
{
	x_json_t	vObject = x_json_new_null();
	if(vObject)
	{
		vObject->type = X_JSON_TYPE_NUMBER;
		vObject->value.v_llong = _Value;
	}
	return vObject;
}

// Create an object of type number
_XPOSIXAPI_ x_json_t __xcall__ x_json_new_double(double _Value)
{
	x_json_t	vObject = x_json_new_null();
	if(vObject)
	{
		vObject->type = X_JSON_TYPE_DOUBLE;
		vObject->value.v_double = _Value;
	}
	return vObject;
}

// Create an object of type string
_XPOSIXAPI_ x_json_t __xcall__ x_json_new_string(const char* _Value)
{
	x_json_t	vObject = x_json_new_null();
	if(vObject)
	{
		vObject->type = X_JSON_TYPE_STRING;
		vObject->value.v_string = x_posix_strdup(_Value);
	}
	return vObject;
}

// Create an object of type array
_XPOSIXAPI_ x_json_t __xcall__ x_json_new_array()
{
	x_json_t	vObject = x_json_new_null();
	if(vObject)
	{
		vObject->type = X_JSON_TYPE_ARRAY;
	}
	return vObject;
}

// Create an object of type object
_XPOSIXAPI_ x_json_t __xcall__ x_json_new_object()
{
	x_json_t	vObject = x_json_new_null();
	if(vObject)
	{
		vObject->type = X_JSON_TYPE_OBJECT;
	}
	return vObject;
}

// Release an object
_XPOSIXAPI_ void __xcall__ x_json_free(x_json_t _Object)
{
	x_json_t		node = NULL;
	if(_Object == NULL)
	{
		return;
	}

	// Step 1: Release the child
	x_json_free(_Object->child);

	// Step 2: Release the next node
	while(_Object->next)
	{
		node = _Object->next;
		_Object->next = _Object->next->next;
		x_json_free(node);
	}

	// Step 3: Free your own memory
	x_posix_free(_Object->name);
	if(_Object->type == X_JSON_TYPE_STRING)
	{
		x_posix_free(_Object->value.v_string);
	}
	x_posix_free(_Object);
}





// Get the type of the object
_XPOSIXAPI_ int __xcall__ x_json_type(x_json_t _Object)
{
	return _Object->type;
}

// Get the name of the current Json object
_XPOSIXAPI_ const char*  __xcall__ x_json_name(x_json_t _Object)
{
	return _Object->name;
}

// Get the size of the current object, only returned if the object is of type Array or Object
_XPOSIXAPI_ x_size_t  __xcall__ x_json_size(x_json_t _Object)
{
	x_size_t	vSize = 0;
	x_json_t 	vNode = _Object->child;
	if(_Object->type == X_JSON_TYPE_ARRAY || _Object->type == X_JSON_TYPE_OBJECT)
	{
		while(vNode)
		{
			++vSize;
			vNode = vNode->next;
		}
	}
	return vSize;
}





// Check if object type is null
_XPOSIXAPI_ bool __xcall__ x_json_is_null(x_json_t _Object)
{
	return _Object->type == X_JSON_TYPE_NULL;
}

// Check if object type is boolean
_XPOSIXAPI_ bool __xcall__ x_json_is_boolean(x_json_t _Object)
{
	return _Object->type == X_JSON_TYPE_BOOLEAN;
}

// Check if object type is number
_XPOSIXAPI_ bool __xcall__ x_json_is_number(x_json_t _Object)
{
	return _Object->type == X_JSON_TYPE_NUMBER || _Object->type == X_JSON_TYPE_DOUBLE;
}

// Check if object type is string
_XPOSIXAPI_ bool __xcall__ x_json_is_string(x_json_t _Object)
{
	return _Object->type == X_JSON_TYPE_STRING;
}

// Check if object type is array
_XPOSIXAPI_ bool __xcall__ x_json_is_array(x_json_t _Object)
{
	return _Object->type == X_JSON_TYPE_ARRAY;
}

// Check if object type is object
_XPOSIXAPI_ bool __xcall__ x_json_is_object(x_json_t _Object)
{
	return _Object->type == X_JSON_TYPE_OBJECT;
}





// Convert the value of the object to boolean
_XPOSIXAPI_ bool __xcall__ x_json_as_boolean(x_json_t _Object)
{
	if(_Object->type == X_JSON_TYPE_BOOLEAN)
	{
		return _Object->value.v_llong;
	}
	return false;
}

// Convert the value of the object to llong
_XPOSIXAPI_ x_int64_t __xcall__ x_json_as_llong(x_json_t _Object)
{
	if(_Object->type == X_JSON_TYPE_NUMBER || _Object->type == X_JSON_TYPE_DOUBLE)
	{
		return _Object->value.v_llong;
	}
	return 0;
}

// Convert the value of the object to ullong
_XPOSIXAPI_ x_uint64_t __xcall__ x_json_as_ullong(x_json_t _Object)
{
	if(_Object->type == X_JSON_TYPE_NUMBER || _Object->type == X_JSON_TYPE_DOUBLE)
	{
		return (x_uint64_t)_Object->value.v_llong;
	}
	return 0;
}

// Convert the value of the object to double
_XPOSIXAPI_ double __xcall__ x_json_as_double(x_json_t _Object)
{
	if(_Object->type == X_JSON_TYPE_NUMBER || _Object->type == X_JSON_TYPE_DOUBLE)
	{
		return _Object->value.v_double;
	}
	return 0.0f;
}

// Convert the value of the object to string
_XPOSIXAPI_ const char* __xcall__ x_json_as_string(x_json_t _Object)
{
	if(_Object->type == X_JSON_TYPE_STRING)
	{
		return (const char*)_Object->value.v_string;
	}
	return NULL;
}





// Get the child of the specified subscript of the json array
_XPOSIXAPI_ x_json_t __xcall__ x_json_array_item(x_json_t _Object, x_size_t _Pos)
{
	x_json_t 	vNode = _Object->child;
	if(_Object->type == X_JSON_TYPE_ARRAY)
	{
		while(vNode && _Pos)
		{
			--_Pos;
			vNode = vNode->next;
		}
		return vNode;
	}
	return NULL;
}

// Add an object at the beginning of the json array
_XPOSIXAPI_ void __xcall__ x_json_array_prepend(x_json_t _Object, x_json_t _Item)
{
	if(_Object->type != X_JSON_TYPE_ARRAY)
	{
		return;
	}

	if(_Object->child)
	{
		_Item->next = _Object->child;
		_Object->child->prev = _Item;
		_Object->child = _Item;
	}
	else
	{
		_Object->child = _Item;
		_Item->prev = NULL;
		_Item->next = NULL;
	}
}

// Add an object to the end of the json array
_XPOSIXAPI_ void __xcall__ x_json_array_append(x_json_t _Object, x_json_t _Item)
{
	x_json_t 	vNode = _Object->child;
	if(_Object->type != X_JSON_TYPE_ARRAY)
	{
		return;
	}

	if(_Object->child)
	{
		while(vNode->next)
		{
			vNode = vNode->next;
		}
		vNode->next = _Item;
		_Item->prev = vNode;
		_Item->next = NULL;
	}
	else
	{
		_Object->child = _Item;
		_Item->prev = NULL;
		_Item->next = NULL;
	}
}

// Insert an object at the specified subscript of the json array
_XPOSIXAPI_ void __xcall__ x_json_array_insert(x_json_t _Object, x_size_t _Pos, x_json_t _Item)
{
	x_json_t	vNode = NULL;
	if(_Object->type != X_JSON_TYPE_ARRAY)
	{
		return;
	}

	if(_Pos == 0)
	{
		x_json_array_prepend(_Object, _Item);
	}
	else
	{
		vNode = x_json_array_item(_Object, _Pos);
		if(vNode == NULL)
		{
			x_json_array_append(_Object, _Item);
		}
		else
		{
			if(vNode->next)
			{
				vNode->next->prev = _Item;
			}
			_Item->next = vNode->next;
			_Item->prev = vNode;
			vNode->next = _Item;
		}
	}
}

// Removes the specified child of the Json array object
_XPOSIXAPI_ void __xcall__ x_json_array_remove(x_json_t _Object, x_size_t _Pos)
{
	x_json_t	vNode = x_json_array_detach(_Object, _Pos);
	if(vNode)
	{
		x_json_free(vNode);
	}
}

// Detach the specified children of a Json array object
_XPOSIXAPI_ x_json_t __xcall__ x_json_array_detach(x_json_t _Object, x_size_t _Pos)
{
	x_json_t	vNode = NULL;
	if(_Object->type != X_JSON_TYPE_ARRAY)
	{
		return NULL;
	}

	if(_Pos == 0)
	{
		if(_Object->child)
		{
			vNode = _Object->child;
			_Object->child = _Object->child->next;
			if(_Object->child)
			{
				_Object->child->prev = NULL;
			}
		}
	}
	else
	{
		vNode = x_json_array_item(_Object, _Pos);
		if(vNode)
		{
			if(vNode->next)
			{
				vNode->next->prev = vNode->prev;
			}
			vNode->prev->next = vNode->next;
		}
	}

	if(vNode)
	{
		vNode->prev = NULL;
		vNode->next = NULL;
	}
	return vNode;
}





// Get the child of the specified subscript of the json array
_XPOSIXAPI_ x_json_t __xcall__ x_json_object_item(x_json_t _Object, const char* _Key)
{
	x_json_t 	vNode = _Object->child;
	if(_Object->type == X_JSON_TYPE_OBJECT && _Key)
	{
		while(vNode)
		{
			if(vNode->name && 0 == x_posix_strcmp(vNode->name, _Key))
			{
				break;
			}
			vNode = vNode->next;
		}
		return vNode;
	}
	return NULL;
}

// Insert an object at the specified subscript of the json array
_XPOSIXAPI_ void __xcall__ x_json_object_insert(x_json_t _Object, const char* _Key, x_json_t _Item)
{
	x_json_t 	vNode = _Object->child;
	if(_Object->type != X_JSON_TYPE_OBJECT || _Key == NULL || _Item == NULL)
	{
		return;
	}

	if(_Item->name != _Key)
	{
		x_posix_free(_Item->name);
		_Item->name = x_posix_strdup(_Key);
	}

	vNode = x_json_object_detach(_Object, _Key);
	if(vNode)
	{
		_Item->prev = vNode->prev;
		_Item->next = vNode->next;
		if(vNode == _Object->child)
		{
			_Object->child = _Item;
		}

		// free object
		vNode->prev = NULL;
		vNode->next = NULL;
		x_json_free(vNode);
	}
	else
	{
		if(_Object->child)
		{
			vNode = _Object->child;
			while(vNode->next)
			{
				vNode = vNode->next;
			}

			_Item->next = NULL;
			_Item->prev = vNode;
			vNode->next = _Item;
		}
		else
		{
			_Object->child = _Item;
		}
	}
}

// Removes the specified child of the Json array object
_XPOSIXAPI_ void __xcall__ x_json_object_remove(x_json_t _Object, const char* _Key)
{
	x_json_t	vNode = x_json_object_detach(_Object, _Key);
	if(vNode)
	{
		x_json_free(vNode);
	}
}

// Detach the specified children of a Json array object
_XPOSIXAPI_ x_json_t __xcall__ x_json_object_detach(x_json_t _Object, const char* _Key)
{
	x_json_t	vNode = NULL;
	if(_Object->type != X_JSON_TYPE_OBJECT || _Key == NULL)
	{
		return NULL;
	}

	vNode = x_json_object_item(_Object, _Key);
	if(vNode)
	{
		if(vNode->next)
		{
			vNode->next->prev = vNode->prev;
		}
		if(vNode->prev)
		{
			vNode->prev->next = vNode->next;
		}
		else
		{
			_Object->child = NULL;
		}
	}

	if(vNode)
	{
		vNode->prev = NULL;
		vNode->next = NULL;
	}
	return vNode;
}





// Get the forward start iterator of the json object
_XPOSIXAPI_ x_json_iter_t __xcall__ x_json_iter_begin(x_json_t _Object)
{
	return (x_json_iter_t)_Object->child;
}

// Get the forward end iterator of the json object
_XPOSIXAPI_ x_json_iter_t __xcall__ x_json_iter_end(x_json_t _Object)
{
	XCC_UNUSED(_Object);

	return NULL;
}

// child data of the current iterator
_XPOSIXAPI_ x_json_t __xcall__ x_json_iter_data(x_json_t _Object, x_json_iter_t _Iterator)
{
	XCC_UNUSED(_Object);

	return (x_json_t)_Iterator;
}

// the previous iterator of the current iterator
_XPOSIXAPI_ x_json_iter_t __xcall__ x_json_iter_prev(x_json_t _Object, x_json_iter_t _Iterator)
{
	XCC_UNUSED(_Object);

	x_json_t	vNode = (x_json_t)_Iterator;
	return (x_json_iter_t)vNode->prev;
}

// the next iterator of the current iterator
_XPOSIXAPI_ x_json_iter_t __xcall__ x_json_iter_next(x_json_t _Object, x_json_iter_t _Iterator)
{
	XCC_UNUSED(_Object);

	x_json_t	vNode = (x_json_t)_Iterator;
	return (x_json_iter_t)vNode->next;
}

// removes this iterator from the object and returns the next iterator
_XPOSIXAPI_ x_json_iter_t __xcall__ x_json_iter_erase(x_json_t _Object, x_json_iter_t _Iterator)
{
	x_json_t	vCurrent = _Object->child;
	x_json_t	vNode = (x_json_t)_Iterator;
	if(_Object->child && _Iterator)
	{
		if(_Object->child == vNode)
		{
			_Object->child = _Object->child->next;
			if(_Object->child)
			{
				_Object->child->prev = NULL;
			}

			// free node
			vNode->prev = NULL;
			vNode->next = NULL;
			x_json_free(vNode);

			return (x_json_iter_t)_Object->child;
		}
		else
		{
			while(vCurrent)
			{
				if(vCurrent == vNode)
				{
					if(vCurrent->next)
					{
						vCurrent->next->prev = vCurrent->prev;
					}
					if(vCurrent->prev)
					{
						vCurrent->prev->next = vCurrent->next;
					}
					_Iterator = (x_json_iter_t)vCurrent->next;

					// free node
					vNode->prev = NULL;
					vNode->next = NULL;
					x_json_free(vNode);

					return _Iterator;
				}
				vCurrent = vCurrent->next;
			}
		}
	}
	return NULL;
}
