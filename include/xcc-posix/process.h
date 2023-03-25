#ifndef			_XCC_POSIX_PROCESS_H_
#define			_XCC_POSIX_PROCESS_H_

#include <xcc-posix/header.h>

XCC_CXX_EXTERN_BEGIN


// X-Series type definition : x_process_stream_t
#if defined(XCC_SYSTEM_WINDOWS)
typedef				HANDLE 				x_process_stream_t;
typedef				DWORD 				x_process_id_t;
#else
typedef				void*				x_process_stream_t;
typedef				pid_t 				x_process_id_t;
#endif
typedef 			x_uint32_t 			x_pid_t;

// Maximum allowed path length
#define 			X_PROC_MAX_NAME			256
#define 			X_PROC_MAX_PATH			4096

// process data type
typedef struct _XCC_process_data
{
	char 			name[X_PROC_MAX_NAME];
	char 			path[X_PROC_MAX_PATH];
	x_process_id_t		id;
}x_process_data_t;



// posix : chdir
_XPOSIXAPI_ int __xcall__ x_posix_chdir(const char* _Directory);

// posix : getcwd
_XPOSIXAPI_ char* __xcall__ x_posix_getcwd(char* _Directory, size_t _Size);

// posix : popen
_XPOSIXAPI_ FILE* __xcall__ x_posix_popen(const char* _Command, const char* _Mode);

// posix : pclose
_XPOSIXAPI_ int __xcall__ x_posix_pclose(FILE* _Stream);

// posix : perror
_XPOSIXAPI_ void __xcall__ x_posix_perror(const char* _ErrorMessage);

// posix : getpid
_XPOSIXAPI_ pid_t __xcall__ x_posix_getpid(void);

// posix : getppid
_XPOSIXAPI_ pid_t __xcall__ x_posix_getppid(void);

// posix : kill
_XPOSIXAPI_ int __xcall__ x_posix_kill(pid_t _Pid, int _Sig);



// Process: 将行参数转换为列表参数
_XPOSIXAPI_ char** __xcall__ x_proc_arg_to_list(const char* _ArgLine);

// Process: 将列表参数转换为行参数
_XPOSIXAPI_ char* __xcall__ x_proc_arg_to_line(const char* const * _ArgList);

// Process: 释放列表参数
_XPOSIXAPI_ void __xcall__ x_proc_arg_free(char** _ArgList);



// Process: 返回当前进程ID
_XPOSIXAPI_ x_pid_t __xcall__ x_proc_get_id();



// This function returns the process identifier of the calling process.
_XPOSIXAPI_ x_process_id_t __xcall__ x_process_get_id();

// Enable process privilege (Windows only)
_XPOSIXAPI_ int __xcall__ x_process_enable_privilege();

// Kill the process with the specified process id
_XPOSIXAPI_ int __xcall__ x_process_kill_id(x_process_id_t _ProcessID, int _Signal);

// Kill the process with the specified process name
_XPOSIXAPI_ int __xcall__ x_process_kill_name(const char* _ProcessName, int _Signal);

// Get data according to process ID
_XPOSIXAPI_ int __xcall__ x_process_get_data_by_id(x_process_id_t _ProcessID, x_process_data_t* _ProcessData);



// Process lookup start
_XPOSIXAPI_ x_process_stream_t __xcall__ x_process_find_first(x_process_data_t* _ProcessData);

// Find the next process. If successful returns 0, Failure returned - 1.
_XPOSIXAPI_ int __xcall__ x_process_find_next(x_process_stream_t _Handle, x_process_data_t* _ProcessData);

// This function closes the specified search handle. If successful returns 0, Failure returned - 1.
_XPOSIXAPI_ int __xcall__ x_process_find_close(x_process_stream_t _Handle);



XCC_CXX_EXTERN_END

#endif
