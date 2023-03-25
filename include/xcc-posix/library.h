#ifndef			_XCC_POSIX_LIBRARY_H_
#define			_XCC_POSIX_LIBRARY_H_

#include <xcc-posix/header.h>

XCC_CXX_EXTERN_BEGIN



// posix : dlopen
_XPOSIXAPI_ void* __xcall__ x_posix_dlopen(const char* _Library, int _Mode);

// posix : dlsym
_XPOSIXAPI_ void* __xcall__ x_posix_dlsym(void* _Handle, const char* _ProcName);

// posix : dlclose
_XPOSIXAPI_ int __xcall__ x_posix_dlclose(void* _Handle);



XCC_CXX_EXTERN_END

#endif
