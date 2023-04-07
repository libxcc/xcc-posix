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



// Compiler attribute: export and import
#if defined(XCC_COMPILER_MSVC)
#define			XCC_COMPILER_API_EXP					__declspec(dllexport)
#define			XCC_COMPILER_API_IMP					__declspec(dllimport)
#define			XCC_COMPILER_API_DEF
#elif defined(XCC_COMPILER_GNUC) || defined(XCC_COMPILER_CLANG)
#define			XCC_COMPILER_API_EXP					__attribute__((visibility("default")))
#define			XCC_COMPILER_API_IMP					__attribute__((visibility("default")))
#define			XCC_COMPILER_API_DEF					__attribute__((visibility("default")))
#else
#define			XCC_COMPILER_API_EXP
#define			XCC_COMPILER_API_IMP
#define			XCC_COMPILER_API_DEF
#endif

// Compiler attribute: deprecated
#if defined(XCC_COMPILER_MSVC)
#define 		XCC_COMPILER_ATTRIBUTE_DEPRECATE			__declspec(deprecated)
#define 		XCC_COMPILER_ATTRIBUTE_DEPRECATE_TEXT(_Text)		__declspec(deprecated(_Text))
#elif defined(XCC_COMPILER_GNUC) || defined(XCC_COMPILER_CLANG)
#define 		XCC_COMPILER_ATTRIBUTE_DEPRECATE			__attribute__((deprecated))
#define 		XCC_COMPILER_ATTRIBUTE_DEPRECATE_TEXT(_Text)		__attribute__((deprecated(_Text)))
#else
#define 		XCC_COMPILER_ATTRIBUTE_DEPRECATE
#define 		XCC_COMPILER_ATTRIBUTE_DEPRECATE_TEXT(_Text)
#endif
#define			XCC_DEPRECATE_OBSOLETE(_Replacement)			XCC_COMPILER_ATTRIBUTE_DEPRECATE_TEXT("This method is obsolete, please use " #_Replacement " first.")

// Compiler attribute: const
#if defined(XCC_COMPILER_GNUC) || defined(XCC_COMPILER_CLANG)
#define 		XCC_COMPILER_ATTRIBUTE_CONST				__attribute__((const))
#else
#define 		XCC_COMPILER_ATTRIBUTE_CONST
#endif

// Compiler attribute: format
#if defined(XCC_COMPILER_GNUC) || defined(XCC_COMPILER_CLANG)
#define 		XCC_COMPILER_ATTRIBUTE_FORMAT(func,m,n)			__attribute__((format(func,m,n)))
#else
#define 		XCC_COMPILER_ATTRIBUTE_FORMAT
#endif



// X-Series cxx compatible export packaging
#if defined(__cplusplus)
#define 		XCC_CXX_EXTERN_CC					extern "C"
#define 		XCC_CXX_EXTERN_BEGIN					extern "C" {
#define 		XCC_CXX_EXTERN_END					}
#else
#define 		XCC_CXX_EXTERN_CC
#define 		XCC_CXX_EXTERN_BEGIN
#define 		XCC_CXX_EXTERN_END
#endif



#endif
