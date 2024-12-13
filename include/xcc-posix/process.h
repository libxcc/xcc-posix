#ifndef			_XCC_POSIX_PROCESS_H_
#define			_XCC_POSIX_PROCESS_H_

#include <xcc-posix/header.h>

XCC_CXX_EXTERN_BEGIN


// X-Series type definition : x_proc_find_t
#if defined(XCC_SYSTEM_WINDOWS)
typedef				DWORD 				x_proc_id_t;
#else
typedef				pid_t 				x_proc_id_t;
#endif
typedef 			x_uint32_t 			x_pid_type;
typedef 			void*				x_proc_find_t;

// Process: Maximum allowed path length
#define 			X_PROC_MAX_NAME			256
#define 			X_PROC_MAX_PATH			4096

// Process: process data type
typedef struct x_proc_data_t
{
	char 			name[X_PROC_MAX_NAME];
	char 			path[X_PROC_MAX_PATH];
	x_pid_type		id;
}x_proc_data_t;



// posix - chdir
_XPOSIXAPI_ int __xcall__ x_posix_chdir(const char* _Directory);

// posix - getcwd
_XPOSIXAPI_ char* __xcall__ x_posix_getcwd(char* _Directory, size_t _Size);

// posix - popen
_XPOSIXAPI_ FILE* __xcall__ x_posix_popen(const char* _Command, const char* _Mode);

// posix - pclose
_XPOSIXAPI_ int __xcall__ x_posix_pclose(FILE* _Stream);

// posix - perror
_XPOSIXAPI_ void __xcall__ x_posix_perror(const char* _ErrorMessage);

// posix - getpid
_XPOSIXAPI_ pid_t __xcall__ x_posix_getpid(void);

// posix - getppid
_XPOSIXAPI_ pid_t __xcall__ x_posix_getppid(void);

// posix - kill
_XPOSIXAPI_ int __xcall__ x_posix_kill(pid_t _Pid, int _Sig);



// Process: 将行参数转换为列表参数
_XPOSIXAPI_ char** __xcall__ x_proc_arg_to_list(const char* _ArgLine);

// Process: 将列表参数转换为行参数
_XPOSIXAPI_ char* __xcall__ x_proc_arg_to_line(const char* const * _ArgList);

// Process: 释放列表参数
_XPOSIXAPI_ void __xcall__ x_proc_arg_free(char** _ArgList);



// Process: Returns the current process ID
_XPOSIXAPI_ x_pid_type __xcall__ x_proc_get_id();



// Process: Enable process privilege (Windows only)
_XPOSIXAPI_ int __xcall__ x_proc_enable_privilege();

// Process: Kill the process with the specified process id
_XPOSIXAPI_ int __xcall__ x_proc_kill_id(x_pid_type _ProcessID, int _Signal);

// Process: Kill the process with the specified process name
_XPOSIXAPI_ int __xcall__ x_proc_kill_name(const char* _ProcessName, int _Signal);

// Process: Get data according to process ID
_XPOSIXAPI_ int __xcall__ x_proc_get_data_by_id(x_pid_type _ProcessID, x_proc_data_t* _ProcessData);



// Process: Start traversing the process list.
_XPOSIXAPI_ x_proc_find_t __xcall__ x_proc_find_first(x_proc_data_t* _ProcessData);

// Process: Find the next process. If successful returns 0, Failure returned error code.
_XPOSIXAPI_ int __xcall__ x_proc_find_next(x_proc_find_t _Handle, x_proc_data_t* _ProcessData);

// Process: Close the find handle. If successful returns 0, Failure returned error code.
_XPOSIXAPI_ int __xcall__ x_proc_find_close(x_proc_find_t _Handle);



XCC_CXX_EXTERN_END

#endif
