﻿#ifndef			_XCC_POSIX_SYS_TYPES_H_
#define			_XCC_POSIX_SYS_TYPES_H_

#include <xcc-posix/sys/compiler.h>
#include <xcc-posix/sys/platform.h>
#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <locale.h>
#include <sys/stat.h>
#include <wctype.h>
#include <wchar.h>
#if defined(XCC_SYSTEM_WINDOWS)
#include <WS2tcpip.h>
#include <Windows.h>
#include <direct.h>
#else
#if defined(XCC_SYSTEM_LINUX)
#include <sys/sysmacros.h>
#undef major
#undef minor
#endif
#include <unistd.h>
#include <dirent.h>
#if defined(XCC_SYSTEM_DARWIN)
#include <xlocale.h>
#endif
#endif

XCC_CXX_EXTERN_BEGIN


// X-Series type definition : Integer range
#define 		X_INT16S_MIN					(-32768)
#define 		X_INT16S_MAX					(0x7FFF)
#define 		X_INT16U_MIN					(0U)
#define 		X_INT16U_MAX					(0xFFFFU)
#define 		X_INT32S_MIN					(-2147483647 - 1)
#define 		X_INT32S_MAX					(0x7FFFFFFF)
#define 		X_INT32U_MIN					(0U)
#define 		X_INT32U_MAX					(0xFFFFFFFFU)
#define 		X_INT64S_MIN					(-9223372036854775807 - 1)
#define 		X_INT64S_MAX					(0x7FFFFFFFFFFFFFFFLL)
#define 		X_INT64U_MIN					(0ULL)
#define 		X_INT64U_MAX					(0xFFFFFFFFFFFFFFFFULL)



// X-Series type definition : ssize_t
#if defined(XCC_SYSTEM_WINDOWS) && !defined(__ssize_t_defined)
typedef 		SSIZE_T			ssize_t;
#define __ssize_t_defined
#endif



// X-Series type definition : locale_t
#if defined(XCC_SYSTEM_WINDOWS)
typedef			_locale_t		locale_t;
#endif



// X-Series type definition : mode_t
#if defined(XCC_SYSTEM_WINDOWS)
typedef			unsigned int		mode_t;
#endif



// X-Series type definition : pid_t
#if defined(XCC_SYSTEM_WINDOWS)
typedef			int			pid_t;
#endif



// X-Series type definition : WINAPI
#if !defined(XCC_SYSTEM_WINDOWS) && !defined(WINAPI)
#define			WINAPI			__xcall__
#endif



// X-Series type definition : HANDLE
#if !defined(XCC_SYSTEM_WINDOWS)
typedef 		void*			HANDLE;
#define			INVALID_HANDLE_VALUE	((HANDLE)(size_t)-1)
#endif
#define 		X_INVALID_HANDLE	((HANDLE)(-1))



// X-Series type definition : HWND
#if !defined(XCC_SYSTEM_WINDOWS)
typedef 		void*			HWND;
#endif



// X-Series type definition : HKEY
#if !defined(XCC_SYSTEM_WINDOWS)
typedef 		void*			HKEY;
#endif



// X-Series type definition : PVOID
#if !defined(XCC_SYSTEM_WINDOWS)
typedef			void*			PVOID;
#endif



// X-Series type definition : NTSTATUS
#if !defined(XCC_SYSTEM_WINDOWS)
typedef			long			NTSTATUS;
#endif



// X-Series type definition : ULONG
#if !defined(XCC_SYSTEM_WINDOWS)
typedef			unsigned long		ULONG;
#endif



// X-Series type definition : PULONG
#if !defined(XCC_SYSTEM_WINDOWS)
typedef			unsigned long*		PULONG;
#endif



// X-Series type definition : DWORD
#if !defined(XCC_SYSTEM_WINDOWS)
typedef			unsigned long		DWORD;
#endif



// X-Series type definition : SOCKET
#if !defined(XCC_SYSTEM_WINDOWS)
typedef			unsigned int		SOCKET;
#endif



// X-Series type definition : DIR
#if defined(XCC_COMPILER_MSVC)
typedef struct dirent
{
	long					d_ino;			/* inode number */
	off_t					d_off;			/* offset to this dirent */
	unsigned short				d_reclen;		/* length of this d_name */
	unsigned char				d_type;			/* the type of d_name */
	char					d_name[MAX_PATH];	/* file name (null-terminated) */
}dirent;
typedef struct __dirstream
{
	void*					__fd;			/* `struct hurd_fd' pointer for descriptor.   */
	char*					__data;			/* Directory block.   */
	int					__entry_data;		/* Entry number `__data' corresponds to.   */
	char*					__ptr;			/* Current pointer into the block.   */
	int					__entry_ptr;		/* Entry number `__ptr' corresponds to.   */
	size_t					__allocation;		/* Space allocated for the block.   */
	size_t					__size;			/* Total valid data in the block.   */

	char*					__directory;		/* Directory path */
	void*					__finddata64;		/* Compatible _findfirst64 */
	void*					__dirent;
}DIR;
#endif



// X-Series type definition : Basic types
typedef		char				x_int8_t;
typedef		unsigned char			x_uint8_t;
typedef		short				x_int16_t;
typedef		unsigned short			x_uint16_t;
typedef		int				x_int32_t;
typedef		unsigned int			x_uint32_t;
typedef		long long			x_int64_t;
typedef		unsigned long long		x_uint64_t;



// X-Series type definition : Platform bits
#if defined(XCC_PLATFORM_BIT_32)
typedef		int				x_ssize_t;
typedef		unsigned int			x_size_t;
#else
typedef		long long			x_ssize_t;
typedef		unsigned long long		x_size_t;
#endif



// X-Series type definition : Range types
typedef 	x_size_t			x_pos_type;
typedef 	x_ssize_t			x_diff_type;
typedef 	x_int64_t			x_time_type;



XCC_CXX_EXTERN_END

#endif
