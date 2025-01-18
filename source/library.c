#include <xcc-posix/library.h>
#include <xcc-posix/string.h>
#include <xcc-posix/memory.h>
#if defined(XCC_SYSTEM_WINDOWS)
#include <xcc-posix/stream.h>
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

// posix - dlerror
_XPOSIXAPI_ const char* __xcall__ x_posix_dlerror()
{
#if defined(XCC_SYSTEM_WINDOWS)
	static char*	static_object_example = NULL;
	if(static_object_example)
	{
		x_posix_free(static_object_example);
		static_object_example = NULL;
	}

	// 格式化错误代码并获取相应的消息
	DWORD 		vError = GetLastError();
	LPSTR		vMessage = NULL;
	size_t		vSize = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, vError, 0, (LPSTR)&vMessage, 0, NULL);
	if(vSize)
	{
		static_object_example = x_posix_strdup(vMessage);
	}
	else
	{
		char		vFormat[32] = {0};
		x_posix_sprintf(vFormat, "GetLastError: %u", vError);
		static_object_example = x_posix_strdup(vFormat);
	}
	LocalFree(vMessage);

	return static_object_example;
#else
	return dlerror();
#endif
}
