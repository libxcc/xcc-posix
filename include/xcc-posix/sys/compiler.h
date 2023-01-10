#ifndef			_XCC_POSIX_SYS_COMPILER_H_
#define			_XCC_POSIX_SYS_COMPILER_H_


/// ********** ********** ********** ********** ********** **********
/// Information about the current compiler
/// ********** ********** ********** ********** ********** **********


// Compiler : MSVC
#if defined(_MSC_VER)
#define 		XCC_COMPILER_MSVC			(1)
#endif

// Compiler : CLANG
#if defined(__clang__)
#define 		XCC_COMPILER_CLANG			(1)
#endif

// Compiler : GNUC
#if defined(__GNUC__)
#define 		XCC_COMPILER_GNUC			(1)
#endif


// Check whether the compiler supports
#if !defined(XCC_COMPILER_MSVC) && !defined(XCC_COMPILER_GNUC) && !defined(XCC_COMPILER_CLANG)
#error This compiler is not supported yet
#endif



// Compiler export and import definitions
#if defined(XCC_COMPILER_MSVC)
#define			XCC_COMPILER_API_EXP			__declspec(dllexport)
#define			XCC_COMPILER_API_IMP			__declspec(dllimport)
#define			XCC_COMPILER_API_DEF
#elif defined(XCC_COMPILER_GNUC) || defined(XCC_COMPILER_CLANG)
#define			XCC_COMPILER_API_EXP			__attribute__((visibility("default")))
#define			XCC_COMPILER_API_IMP			__attribute__((visibility("default")))
#define			XCC_COMPILER_API_DEF			__attribute__((visibility("default")))
#else
#define			XCC_COMPILER_API_EXP
#define			XCC_COMPILER_API_IMP
#define			XCC_COMPILER_API_DEF
#endif



// X-Series cxx compatible export packaging
#if defined(__cplusplus)
#define 		XCC_CXX_EXTERN_BEGIN			extern "C" {
#else
#define 		XCC_CXX_EXTERN_BEGIN
#endif
#if defined(__cplusplus)
#define 		XCC_CXX_EXTERN_END			}
#else
#define 		XCC_CXX_EXTERN_END
#endif


#endif
