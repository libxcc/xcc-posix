﻿#ifndef			_XCC_POSIX_TIME_H_
#define			_XCC_POSIX_TIME_H_

#include <xcc-posix/header.h>

XCC_CXX_EXTERN_BEGIN



// posix : srand
_XPOSIXAPI_ void __xcall__ x_posix_srand(unsigned int _Seed);

// posix : rand
_XPOSIXAPI_ int __xcall__ x_posix_rand(void);

// posix : time
_XPOSIXAPI_ time_t __xcall__ x_posix_time(time_t* _Seconds);

// posix : sleep
_XPOSIXAPI_ unsigned int __xcall__ x_posix_sleep(unsigned int _Seconds);

// posix : msleep
_XPOSIXAPI_ unsigned int __xcall__ x_posix_msleep(unsigned int _Milliseconds);

// posix : usleep
_XPOSIXAPI_ unsigned int __xcall__ x_posix_usleep(unsigned int _Microseconds);



// 获取当前系统时间的总秒数
_XPOSIXAPI_ x_time_type __xcall__ x_time_system_second();

// 获取当前系统时间的总毫秒数
_XPOSIXAPI_ x_time_type __xcall__ x_time_system_millisecond();

// 获取当前系统时间的总微秒数
_XPOSIXAPI_ x_time_type __xcall__ x_time_system_microsecond();



// 高精度计时器: 创建
_XPOSIXAPI_ HANDLE __xcall__ x_time_hpt_new();

// 高精度计时器: 重置
_XPOSIXAPI_ void __xcall__ x_time_hpt_reset(HANDLE _Handle);

// 高精度计时器: 计算
_XPOSIXAPI_ x_time_type __xcall__ x_time_hpt_calc(HANDLE _Handle);

// 高精度计时器: 释放
_XPOSIXAPI_ x_time_type __xcall__ x_time_hpt_free(HANDLE _Handle);



XCC_CXX_EXTERN_END

#endif
