#include <xcc-posix/library.h>
#include <xcc-posix/string.h>
#include <xcc-posix/memory.h>
#if defined(XCC_SYSTEM_WINDOWS)
#else
#include <dlfcn.h>
#endif



// posix - dlopen
_XPOSIXAPI_ void* __xcall__ x_posix_dlopen(const char* _Library, int _Mode)
{
#if defined(XCC_SYSTEM_WINDOWS)
	XCC_UNUSED(_Mode);

	void*		vHandle = NULL;
	wchar_t*	vLocalLibrary = x_posix_strutow(_Library);
	if(vLocalLibrary)
	{
		vHandle = LoadLibraryW(vLocalLibrary);
		x_posix_free(vLocalLibrary);
	}
	return vHandle;
#else
	return dlopen(_Library, _Mode);
#endif
}

// posix - dlsym
_XPOSIXAPI_ void* __xcall__ x_posix_dlsym(void* _Handle, const char* _ProcName)
{
#if defined(XCC_SYSTEM_WINDOWS)
	return (void*)GetProcAddress(_Handle, _ProcName);
#else
	return dlsym(_Handle, _ProcName);
#endif
}

// posix - dlclose
_XPOSIXAPI_ int __xcall__ x_posix_dlclose(void* _Handle)
{
#if defined(XCC_SYSTEM_WINDOWS)
	return FreeLibrary(_Handle) ? 0 : 1;
#else
	return dlclose(_Handle);
#endif
}
