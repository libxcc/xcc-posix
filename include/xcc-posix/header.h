#ifndef			_XCC_POSIX_HEADER_H_
#define			_XCC_POSIX_HEADER_H_

#include <xcc-posix/sys/compiler.h>
#include <xcc-posix/sys/macro.h>
#include <xcc-posix/sys/platform.h>
#include <xcc-posix/sys/types.h>



// X-Series macro definition: call
#if defined(XCC_COMPILER_MSVC)
#define			XCC_POSIX_CALL					__cdecl
#elif defined(XCC_COMPILER_GNUC) || defined(XCC_COMPILER_CLANG)
// #define		XCC_POSIX_CALL					__attribute__((__cdecl__))
#define			XCC_POSIX_CALL
#else
#define			XCC_POSIX_CALL
#endif
#define			__xcall__					XCC_POSIX_CALL



// X-Series macro definition: Platform
#define			__XFILE__					__FILE__
#define			__XLINE__					__LINE__
#if defined(XCC_COMPILER_MSVC)
#define			__XFUNCTION__					__FUNCTION__
#else
#define			__XFUNCTION__					__func__
#endif
#if defined(XCC_COMPILER_MSVC)
#define			__XFUNCSIG__					__FUNCSIG__
#else
#define			__XFUNCSIG__					__PRETTY_FUNCTION__
#endif
#define			__XTIMESTAMP__					__TIMESTAMP__



// X-Series macro definition: Export
#if defined(XCC_POSIX_BUILD_STATIC)
#define			_XPOSIXAPI_
#else
#if defined(XCC_POSIX_BUILD_LOCAL)
#define			_XPOSIXAPI_					XCC_COMPILER_API_EXP
#else
#define			_XPOSIXAPI_					XCC_COMPILER_API_IMP
#endif
#endif



// X-Series macro definition: Control
#define 		XCC_UNUSED(_Param)				((void)_Param)
#define			XCC_PATH_MAX					(1024)
#define			XCC_STDIO_VSNPRINTF_EXTRA			(10)



#endif
