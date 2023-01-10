#include <xcc-posix/memory.h>



// posix : malloc
_XPOSIXAPI_ void* __xcall__ x_posix_malloc(size_t _Size)
{
	return malloc(_Size);
}

// posix : calloc
_XPOSIXAPI_ void* __xcall__ x_posix_calloc(size_t _Count, size_t _Size)
{
	return calloc(_Count, _Size);
}

// posix : realloc
_XPOSIXAPI_ void* __xcall__ x_posix_realloc(void* _Block, size_t _Size)
{
	return realloc(_Block, _Size);
}

// posix : memdup
_XPOSIXAPI_ void* __xcall__ x_posix_memdup(const void* _Memory, size_t _Size)
{
	if(_Memory == NULL || _Size == 0)
	{
		return NULL;
	}
	void*		vTarget = x_posix_malloc(_Size);
	if(vTarget)
	{
		x_posix_memcpy(vTarget, _Memory, _Size);
	}
	return vTarget;
}

// posix : free
_XPOSIXAPI_ void __xcall__ x_posix_free(void* _Memory)
{
	free(_Memory);
}





// posix : memset
_XPOSIXAPI_ void* __xcall__ x_posix_memset(void* _Memory, int _Value, size_t _Size)
{
	return memset(_Memory, _Value, _Size);
}

// posix : memcpy
_XPOSIXAPI_ void* __xcall__ x_posix_memcpy(void* _Dst, const void* _Src, size_t _Size)
{
	return memcpy(_Dst, _Src, _Size);
}

// posix : memmove
_XPOSIXAPI_ void* __xcall__ x_posix_memmove(void* _Dst, const void* _Src, size_t _Size)
{
	return memmove(_Dst, _Src, _Size);
}

// posix : memchr
_XPOSIXAPI_ void* __xcall__ x_posix_memchr(const void* _Buf, int _Val, size_t _MaxCount)
{
	return memchr(_Buf, _Val, _MaxCount);
}

// posix : memrchr
_XPOSIXAPI_ void* __xcall__ x_posix_memrchr(const void* _Buf, int _Val, size_t _MaxCount)
{
	if(_Buf == NULL || _MaxCount == 0)
	{
		return NULL;
	}

	unsigned char		vChar = (unsigned char)_Val;
	const unsigned char*	vBegin = ((const unsigned char*)_Buf);
	const unsigned char*	vMemory = vBegin + _MaxCount - 1;

	while(*vMemory != vChar && vMemory >= vBegin)
	{
		--vMemory;
	}
	if(vMemory < vBegin)
	{
		return NULL;
	}
	return (void*)vMemory;
}

// posix : memcmp
_XPOSIXAPI_ int __xcall__ x_posix_memcmp(const void* _Buf1, const void* _Buf2, size_t _Size)
{
	return memcmp(_Buf1, _Buf2, _Size);
}

// posix : memrev
_XPOSIXAPI_ void* __xcall__ x_posix_memrev(void* _Memory, size_t _Size)
{
	char*		vMemory = (char*)_Memory;
	size_t 		vCount = _Size >> 1;
	char 		vTemp = 0;

	for(size_t vIndex = 0; vIndex < vCount; ++vIndex)
	{
		vTemp = vMemory[vIndex];
		vMemory[vIndex] = vMemory[_Size - vIndex - 1];
		vMemory[_Size - vIndex - 1] = vTemp;
	}
	return vMemory;
}

// posix : memmem
_XPOSIXAPI_ const void* __xcall__ x_posix_memmem(const void* _SrcBuf, size_t _SrcLen, const void* _SubMem, size_t _SubLen)
{
	if(_SrcBuf == NULL || _SrcLen == 0 || _SubMem == NULL || _SubLen == 0 || _SrcLen < _SubLen)
	{
		return NULL;
	}

	const char*		cur = _SrcBuf;
	const char*		last = cur + _SrcLen - _SubLen;
	const char*		sub = (const char*)_SubMem;

	for(; cur <= last; ++cur)
	{
		if (cur[0] == sub[0] && memcmp(cur, sub, _SubLen) == 0)
		{
			return cur;
		}
	}
	return NULL;
}





// posix : wmemset
_XPOSIXAPI_ wchar_t* __xcall__ x_posix_wmemset(wchar_t* _Memory, wchar_t _Value, size_t _Size)
{
	return wmemset(_Memory, _Value, _Size);
}

// posix : wmemcpy
_XPOSIXAPI_ wchar_t* __xcall__ x_posix_wmemcpy(wchar_t* _Dst, const wchar_t* _Src, size_t _Size)
{
	return wmemcpy(_Dst, _Src, _Size);
}

// posix : wmemmove
_XPOSIXAPI_ wchar_t* __xcall__ x_posix_wmemmove(wchar_t* _Dst, const wchar_t* _Src, size_t _Size)
{
	return wmemmove(_Dst, _Src, _Size);
}

// posix : wmemchr
_XPOSIXAPI_ const wchar_t* __xcall__ x_posix_wmemchr(const wchar_t* _Buf, wchar_t _Val, size_t _MaxCount)
{
	return wmemchr(_Buf, _Val, _MaxCount);
}

// posix : wmemrchr
_XPOSIXAPI_ const wchar_t* __xcall__ x_posix_wmemrchr(const wchar_t* _Buf, wchar_t _Val, size_t _MaxCount)
{
	if(_Buf == NULL || _MaxCount == 0)
	{
		return NULL;
	}

	wchar_t			vChar = _Val;
	const wchar_t*		vBegin = _Buf;
	const wchar_t*		vMemory = vBegin + _MaxCount - 1;

	while(*vMemory != vChar && vMemory >= vBegin)
	{
		--vMemory;
	}
	if(vMemory < vBegin)
	{
		return NULL;
	}
	return (void*)vMemory;
}

// posix : wmemcmp
_XPOSIXAPI_ int __xcall__ x_posix_wmemcmp(const wchar_t* _Buf1, const wchar_t* _Buf2, size_t _Size)
{
	return wmemcmp(_Buf1, _Buf2, _Size);
}

// posix : wmemrev
_XPOSIXAPI_ wchar_t* __xcall__ x_posix_wmemrev(wchar_t* _Memory, size_t _Size)
{
	wchar_t*	vMemory = (wchar_t*)_Memory;
	size_t 		vCount = _Size >> 1;
	wchar_t 	vTemp = 0;

	for(size_t vIndex = 0; vIndex < vCount; ++vIndex)
	{
		vTemp = vMemory[vIndex];
		vMemory[vIndex] = vMemory[_Size - vIndex - 1];
		vMemory[_Size - vIndex - 1] = vTemp;
	}
	return vMemory;
}

// posix : wmemmem
_XPOSIXAPI_ const wchar_t* __xcall__ x_posix_wmemmem(const wchar_t* _SrcBuf, size_t _SrcLen, const wchar_t* _SubMem, size_t _SubLen)
{
	if(_SrcBuf == NULL || _SrcLen == 0 || _SubMem == NULL || _SubLen == 0 || _SrcLen < _SubLen)
	{
		return NULL;
	}

	const wchar_t*		cur = _SrcBuf;
	const wchar_t*		last = cur + _SrcLen - _SubLen;
	const wchar_t*		sub = (const wchar_t*)_SubMem;

	for(; cur <= last; ++cur)
	{
		if (cur[0] == sub[0] && wmemcmp(cur, sub, _SubLen) == 0)
		{
			return cur;
		}
	}
	return NULL;
}
