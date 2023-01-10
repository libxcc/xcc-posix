﻿#ifndef			_XCC_POSIX_SYS_PLATFORM_H_
#define			_XCC_POSIX_SYS_PLATFORM_H_


/// ********** ********** ********** ********** ********** **********
/// Target OS Definition
/// ********** ********** ********** ********** ********** **********


// X-Series Platform Definition : Windows
#if defined(_WIN32)
#define			XCC_SYSTEM_WINDOWS			(1)
#endif

// X-Series Platform Definition : Linux
#if defined (__linux__) || defined (_LINUX_)
#define			XCC_SYSTEM_LINUX			(1)
#endif

// X-Series Platform Definition : Darwin
#if defined (__APPLE__)
#define			XCC_SYSTEM_DARWIN			(1)
#endif

// X-Series Platform Definition : Android
#if defined (__ANDROID__) || defined (ANDROID)
#define			XCC_SYSTEM_ANDROID			(1)
#endif

// X-Series Platform Definition : ARM
#if defined (__arm__) || defined (__ARM_ARCH)
#define 		XCC_SYSTEM_ARM				(1)
#endif


// Check if the OS is supported
#if !defined(XCC_SYSTEM_WINDOWS) && !defined(XCC_SYSTEM_DARWIN) && !defined(XCC_SYSTEM_LINUX)
#error This compiler is not supported yet
#endif





// Target platform bits
#if defined(__x86_64__) || defined(__amd64__) || defined(_WIN64) || defined(__aarch64__)
#define 		XCC_PLATFORM_BIT_64			(1)
#elif defined(__i386__) || defined(_WIN32) || defined(__arm__)
#define 		XCC_PLATFORM_BIT_32			(1)
#else
#error This compiler is not supported yet
#endif


#endif
