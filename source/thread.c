#include <xcc-posix/thread.h>
#include <sys/types.h>
#if !defined(XCC_SYSTEM_WINDOWS)
#include <unistd.h>
#include <sys/syscall.h>
#include <signal.h>
#include <errno.h>
#endif



// posix : gettid
_XPOSIXAPI_ pid_t __xcall__ x_posix_gettid(void)
{
#if defined(XCC_SYSTEM_WINDOWS)
	return (pid_t)GetCurrentThreadId();
#endif
#if defined(XCC_SYSTEM_LINUX)
	return (pid_t)syscall(SYS_gettid);
#endif
#if defined(XCC_SYSTEM_DARWIN)
	uint64_t	vThreadID = 0;
	pthread_threadid_np(NULL, &vThreadID);
	return (pid_t)vThreadID;
#endif
}



// Thread: 设置线程名称
_XPOSIXAPI_ int __xcall__ x_thread_set_name(const char* _ThreadName)
{
#if defined(XCC_SYSTEM_WINDOWS)
	const DWORD MS_VC_EXCEPTION=0x406D1388;
#pragma pack(push,8)
	typedef struct tagTHREAD_NAME_INFO
	{
		DWORD dwType; // Must be 0x1000.
		LPCSTR szName; // Pointer to name (in user addr space).
		DWORD dwThreadID; // Thread ID (-1=caller thread).
		DWORD dwFlags; // Reserved for future use, must be zero.
	}THREAD_NAME_INFO;
#pragma pack(pop)

	THREAD_NAME_INFO info;
	info.dwType = 0x1000;
	info.szName = _ThreadName;
	info.dwThreadID = GetCurrentThreadId();
	info.dwFlags = 0;

	__try
	{
		RaiseException( MS_VC_EXCEPTION, 0, sizeof(info)/sizeof(ULONG_PTR), (ULONG_PTR*)&info );
	}
	__except(EXCEPTION_CONTINUE_EXECUTION)
	{
		return (int)GetLastError();
	}
	return 0;
#else
	return -1;
#endif
}



/// Create a thread
_XPOSIXAPI_ x_thread_t __xcall__ x_thread_create(x_thread_func_t _Address, void* _Param)
{
#if defined(XCC_SYSTEM_WINDOWS)
	return CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)_Address, _Param, 0, 0);
#else
	typedef void*(*LPTHREAD_START_ROUTINE)(void*);
	pthread_t	vHandle = 0;
	pthread_create(&vHandle, NULL, (LPTHREAD_START_ROUTINE)_Address, _Param);
	return vHandle;
#endif
}

/// Thread detach
_XPOSIXAPI_ void __xcall__ x_thread_detach(x_thread_t _Thread)
{
#if defined(XCC_PARAMETER_VALIDATION)
	if(_Thread == X_THREAD_INVALID_HANDLE)
	{
		return;
	}
#endif
#if defined(XCC_SYSTEM_WINDOWS)
	CloseHandle(_Thread);
#else
	pthread_detach(_Thread);
#endif
}

/// Gets the ID of the thread itself.
_XPOSIXAPI_ x_thread_t __xcall__ x_thread_self()
{
#if defined(XCC_SYSTEM_WINDOWS)
	return GetCurrentThread();
#else
	return pthread_self();
#endif
}

/// Wait for the end of a thread
_XPOSIXAPI_ int __xcall__ x_thread_join(x_thread_t _Thread)
{
#if defined(XCC_PARAMETER_VALIDATION)
	if(_Thread == X_THREAD_INVALID_HANDLE)
	{
		return EINVAL;
	}
#endif
#if defined(XCC_SYSTEM_WINDOWS)
	return (int)WaitForSingleObject(_Thread, INFINITE);
#else
	return pthread_join(_Thread, NULL);
#endif
}

/// Check whether the thread is alive
_XPOSIXAPI_ int __xcall__ x_thread_alive(x_thread_t _Thread)
{
#if defined(XCC_PARAMETER_VALIDATION)
	if(_Thread == X_THREAD_INVALID_HANDLE)
	{
		return EINVAL;
	}
#endif
#if defined(XCC_SYSTEM_WINDOWS)
	if(WaitForSingleObject(_Thread, 0) == WAIT_TIMEOUT)
	{
		return 0;
	}
	else
	{
		return (int)GetLastError();
	}
#else
	return pthread_kill(_Thread, 0);
#endif
}

/// Kill the specified thread
_XPOSIXAPI_ int __xcall__ x_thread_kill(x_thread_t _Thread)
{
#if defined(XCC_PARAMETER_VALIDATION)
	if(_Thread == X_THREAD_INVALID_HANDLE)
	{
		return EINVAL;
	}
#endif
#if defined(XCC_SYSTEM_WINDOWS)
	if(TerminateThread(_Thread, 0))
	{
		return 0;
	}
	else
	{
		return (int)GetLastError();
	}
#else
	return pthread_kill(_Thread, 9);
#endif
}
