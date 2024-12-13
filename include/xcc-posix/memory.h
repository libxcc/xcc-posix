#ifndef			_XCC_POSIX_MEMORY_H_
#define			_XCC_POSIX_MEMORY_H_

#include <xcc-posix/header.h>

XCC_CXX_EXTERN_BEGIN



// posix - malloc
_XPOSIXAPI_ void* __xcall__ x_posix_malloc(size_t _Size);

// posix - calloc
_XPOSIXAPI_ void* __xcall__ x_posix_calloc(size_t _Count, size_t _Size);

// posix - realloc
_XPOSIXAPI_ void* __xcall__ x_posix_realloc(void* _Block, size_t _Size);

// posix - memdup
_XPOSIXAPI_ void* __xcall__ x_posix_memdup(const void* _Memory, size_t _Size);

// posix - free
_XPOSIXAPI_ void __xcall__ x_posix_free(void* _Memory);





// posix - memset
_XPOSIXAPI_ void* __xcall__ x_posix_memset(void* _Memory, int _Value, size_t _Size);

// posix - memcpy
_XPOSIXAPI_ void* __xcall__ x_posix_memcpy(void* _Dst, const void* _Src, size_t _Size);

// posix - memmove
_XPOSIXAPI_ void* __xcall__ x_posix_memmove(void* _Dst, const void* _Src, size_t _Size);

// posix - memchr
_XPOSIXAPI_ void* __xcall__ x_posix_memchr(const void* _Buf, int _Val, size_t _MaxCount);

// posix - memrchr
_XPOSIXAPI_ void* __xcall__ x_posix_memrchr(const void* _Buf, int _Val, size_t _MaxCount);

// posix - memcmp
_XPOSIXAPI_ int __xcall__ x_posix_memcmp(const void* _Buf1, const void* _Buf2, size_t _Size);

// posix - memrev
_XPOSIXAPI_ void* __xcall__ x_posix_memrev(void* _Memory, size_t _Size);

// posix - memmem
_XPOSIXAPI_ const void* __xcall__ x_posix_memmem(const void* _SrcBuf, size_t _SrcLen, const void* _SubMem, size_t _SubLen);





// posix - wmemset
_XPOSIXAPI_ wchar_t* __xcall__ x_posix_wmemset(wchar_t* _Memory, wchar_t _Value, size_t _Size);

// posix - wmemcpy
_XPOSIXAPI_ wchar_t* __xcall__ x_posix_wmemcpy(wchar_t* _Dst, const wchar_t* _Src, size_t _Size);

// posix - wmemmove
_XPOSIXAPI_ wchar_t* __xcall__ x_posix_wmemmove(wchar_t* _Dst, const wchar_t* _Src, size_t _Size);

// posix - wmemchr
_XPOSIXAPI_ const wchar_t* __xcall__ x_posix_wmemchr(const wchar_t* _Buf, wchar_t _Val, size_t _MaxCount);

// posix - wmemrchr
_XPOSIXAPI_ const wchar_t* __xcall__ x_posix_wmemrchr(const wchar_t* _Buf, wchar_t _Val, size_t _MaxCount);

// posix - wmemcmp
_XPOSIXAPI_ int __xcall__ x_posix_wmemcmp(const wchar_t* _Buf1, const wchar_t* _Buf2, size_t _Size);

// posix - wmemrev
_XPOSIXAPI_ wchar_t* __xcall__ x_posix_wmemrev(wchar_t* _Memory, size_t _Size);

// posix - wmemmem
_XPOSIXAPI_ const wchar_t* __xcall__ x_posix_wmemmem(const wchar_t* _SrcBuf, size_t _SrcLen, const wchar_t* _SubMem, size_t _SubLen);



XCC_CXX_EXTERN_END

#endif
