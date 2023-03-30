#ifndef			_XCC_POSIX_JSON_H_
#define			_XCC_POSIX_JSON_H_

#include <xcc-posix/header.h>

XCC_CXX_EXTERN_BEGIN


// json data
struct x_json_data;
typedef struct x_json_data*			x_json_t;

// json iterator type
struct x_json_iter_data;
typedef struct x_json_iter_data*		x_json_iter_t;

#define X_JSON_TYPE_NULL			(0)
#define X_JSON_TYPE_BOOLEAN			(1)
#define X_JSON_TYPE_NUMBER			(2)
#define X_JSON_TYPE_STRING			(3)
#define X_JSON_TYPE_ARRAY			(4)
#define X_JSON_TYPE_OBJECT			(5)

#define X_JSON_FORMAT_NULL			(0)
#define X_JSON_FORMAT_TAB			(1)



// Parse String to Json
_XPOSIXAPI_ x_json_t __xcall__ x_json_parse(const char* _String);

// Format Json to string
_XPOSIXAPI_ char* __xcall__ x_json_print(x_json_t _Object);

// Format Json to string
_XPOSIXAPI_ char* __xcall__ x_json_printf(x_json_t _Object, int _Format);

// Clone a Json
_XPOSIXAPI_ x_json_t __xcall__ x_json_clone(x_json_t _Object);





// Create an object of type null
_XPOSIXAPI_ x_json_t __xcall__ x_json_new_null();

// Create an object of type boolean
_XPOSIXAPI_ x_json_t __xcall__ x_json_new_boolean(bool _Value);

// Create an object of type number
_XPOSIXAPI_ x_json_t __xcall__ x_json_new_number(x_int64_t _Value);

// Create an object of type number
_XPOSIXAPI_ x_json_t __xcall__ x_json_new_double(double _Value);

// Create an object of type string
_XPOSIXAPI_ x_json_t __xcall__ x_json_new_string(const char* _Value);

// Create an object of type array
_XPOSIXAPI_ x_json_t __xcall__ x_json_new_array();

// Create an object of type object
_XPOSIXAPI_ x_json_t __xcall__ x_json_new_object();

// Release an object
_XPOSIXAPI_ void __xcall__ x_json_free(x_json_t _Object);





// Get the type of the object
_XPOSIXAPI_ int __xcall__ x_json_type(x_json_t _Object);

// Get the name of the current Json object
_XPOSIXAPI_ const char*  __xcall__ x_json_name(x_json_t _Object);

// Get the size of the current object, only returned if the object is of type Array or Object
_XPOSIXAPI_ x_size_t  __xcall__ x_json_size(x_json_t _Object);





// Check if object type is null
_XPOSIXAPI_ bool __xcall__ x_json_is_null(x_json_t _Object);

// Check if object type is boolean
_XPOSIXAPI_ bool __xcall__ x_json_is_boolean(x_json_t _Object);

// Check if object type is number
_XPOSIXAPI_ bool __xcall__ x_json_is_number(x_json_t _Object);

// Check if object type is string
_XPOSIXAPI_ bool __xcall__ x_json_is_string(x_json_t _Object);

// Check if object type is array
_XPOSIXAPI_ bool __xcall__ x_json_is_array(x_json_t _Object);

// Check if object type is object
_XPOSIXAPI_ bool __xcall__ x_json_is_object(x_json_t _Object);





// Convert the value of the object to boolean
_XPOSIXAPI_ bool __xcall__ x_json_as_boolean(x_json_t _Object);

// Convert the value of the object to llong
_XPOSIXAPI_ x_int64_t __xcall__ x_json_as_llong(x_json_t _Object);

// Convert the value of the object to ullong
_XPOSIXAPI_ x_uint64_t __xcall__ x_json_as_ullong(x_json_t _Object);

// Convert the value of the object to double
_XPOSIXAPI_ double __xcall__ x_json_as_double(x_json_t _Object);

// Convert the value of the object to string
_XPOSIXAPI_ const char* __xcall__ x_json_as_string(x_json_t _Object);





// Get the child of the specified subscript of the json array
_XPOSIXAPI_ x_json_t __xcall__ x_json_array_item(x_json_t _Object, x_size_t _Pos);

// Add an object at the beginning of the json array
_XPOSIXAPI_ void __xcall__ x_json_array_prepend(x_json_t _Object, x_json_t _Item);

// Add an object to the end of the json array
_XPOSIXAPI_ void __xcall__ x_json_array_append(x_json_t _Object, x_json_t _Item);

// Insert an object at the specified subscript of the json array
_XPOSIXAPI_ void __xcall__ x_json_array_insert(x_json_t _Object, x_size_t _Pos, x_json_t _Item);

// Removes the specified child of the Json array object
_XPOSIXAPI_ void __xcall__ x_json_array_remove(x_json_t _Object, x_size_t _Pos);

// Detach the specified children of a Json array object
_XPOSIXAPI_ x_json_t __xcall__ x_json_array_detach(x_json_t _Object, x_size_t _Pos);





// Get the child of the specified subscript of the json array
_XPOSIXAPI_ x_json_t __xcall__ x_json_object_item(x_json_t _Object, const char* _Key);

// Insert an object at the specified subscript of the json array
_XPOSIXAPI_ void __xcall__ x_json_object_insert(x_json_t _Object, const char* _Key, x_json_t _Item);

// Removes the specified child of the Json array object
_XPOSIXAPI_ void __xcall__ x_json_object_remove(x_json_t _Object, const char* _Key);

// Detach the specified children of a Json array object
_XPOSIXAPI_ x_json_t __xcall__ x_json_object_detach(x_json_t _Object, const char* _Key);





// Get the forward start iterator of the json object
_XPOSIXAPI_ x_json_iter_t __xcall__ x_json_iter_begin(x_json_t _Object);

// Get the forward end iterator of the json object
_XPOSIXAPI_ x_json_iter_t __xcall__ x_json_iter_end(x_json_t _Object);

// child data of the current iterator
_XPOSIXAPI_ x_json_t __xcall__ x_json_iter_data(x_json_t _Object, x_json_iter_t _Iterator);

// the previous iterator of the current iterator
_XPOSIXAPI_ x_json_iter_t __xcall__ x_json_iter_prev(x_json_t _Object, x_json_iter_t _Iterator);

// the next iterator of the current iterator
_XPOSIXAPI_ x_json_iter_t __xcall__ x_json_iter_next(x_json_t _Object, x_json_iter_t _Iterator);

// removes this iterator from the object and returns the next iterator
_XPOSIXAPI_ x_json_iter_t __xcall__ x_json_iter_erase(x_json_t _Object, x_json_iter_t _Iterator);



XCC_CXX_EXTERN_END

#endif
