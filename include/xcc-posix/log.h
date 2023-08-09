﻿#ifndef			_XCC_POSIX_LOG_H_
#define			_XCC_POSIX_LOG_H_

#include <xcc-posix/header.h>

XCC_CXX_EXTERN_BEGIN


// 日志级别
typedef enum
{
	XLOG_LEVEL_VERBOSE		= 0,
	XLOG_LEVEL_DEBUG		= 1,
	XLOG_LEVEL_INFO			= 2,
	XLOG_LEVEL_WARNING		= 3,
	XLOG_LEVEL_ERROR		= 4,
	XLOG_LEVEL_FATAL		= 5
}x_log_level_t;

// 日志回调声明
typedef int(__xcall__ *xcc_log_printf_cb_t)(x_log_level_t _Level, const char* _TAG, const char* _Message);



/// 设置启用日志锁
/// \param _Enable true为启用，false为不启用
_XPOSIXAPI_ void __xcall__ x_log_set_enable_lock(bool _Enable);

/// 设置日志级别
/// \param _Level 需要启用的日志级别
_XPOSIXAPI_ void __xcall__ x_log_set_level(x_log_level_t _Level);

/// 获取日志级别
/// \return 当前日志级别
_XPOSIXAPI_ x_log_level_t __xcall__ x_log_get_level();

// 设置强制刷新流
_XPOSIXAPI_ void __xcall__ x_log_set_fflush(bool _Status);

/// 设置日志回调
/// 当输出日志时，调用回调函数输出。
/// \param _Function : 如果参数为空，则使用默认输出
_XPOSIXAPI_ void __xcall__ x_log_set_printf_cb(xcc_log_printf_cb_t _Function);

/// 设置日志输出流
/// 当输出日志时，输出在指定的流中。
/// \param _Stream : 如果参数为空，则默认使用stdout
_XPOSIXAPI_ void __xcall__ x_log_set_printf_stream(FILE* _Stream);

/// 以可变参数模式格式化日志输出
/// \param _Level : 日志级别
/// \param _TAG : 日志标签
/// \param _Format : 格式字符串
/// \param ... : 可变参数
_XPOSIXAPI_ int __xcall__ x_log_printf(x_log_level_t _Level, const char* _TAG, const char* _Format, ...);

/// 以参数列表模式格式化日志输出
/// \param _Level : 日志级别
/// \param _TAG : 日志标签
/// \param _Format : 格式字符串
/// \param _ArgList : 参数列表
_XPOSIXAPI_ int __xcall__ x_log_vprintf(x_log_level_t _Level, const char* _TAG, const char* _Format, va_list _ArgList);



// Log convenient call macro
#define			XLOG_VERBOSE(_TAG, _Format, ...)			x_log_printf(XLOG_LEVEL_VERBOSE, _TAG, _Format, ##__VA_ARGS__)
#define			XLOG_DEBUG(_TAG, _Format, ...)				x_log_printf(XLOG_LEVEL_DEBUG, _TAG, _Format, ##__VA_ARGS__)
#define			XLOG_INFO(_TAG, _Format, ...)				x_log_printf(XLOG_LEVEL_INFO, _TAG, _Format, ##__VA_ARGS__)
#define			XLOG_WARNING(_TAG, _Format, ...)			x_log_printf(XLOG_LEVEL_WARNING, _TAG, _Format, ##__VA_ARGS__)
#define			XLOG_ERROR(_TAG, _Format, ...)				x_log_printf(XLOG_LEVEL_ERROR, _TAG, _Format, ##__VA_ARGS__)
#define			XLOG_FATAL(_TAG, _Format, ...)				x_log_printf(XLOG_LEVEL_FATAL, _TAG, _Format, ##__VA_ARGS__)

#define 		XCC_FUNC_V_ENTER					XLOG_VERBOSE(nullptr, u8"[%s : %d] <<<<<<<<<<", __XFUNCTION__, __XLINE__)
#define 		XCC_FUNC_V_EXEC						XLOG_VERBOSE(nullptr, u8"[%s : %d] ----------", __XFUNCTION__, __XLINE__)
#define 		XCC_FUNC_V_LEAVE					XLOG_VERBOSE(nullptr, u8"[%s : %d] >>>>>>>>>>", __XFUNCTION__, __XLINE__)

#define 		XCC_FUNC_D_ENTER					XLOG_DEBUG(nullptr, u8"[%s : %d] <<<<<<<<<<", __XFUNCTION__, __XLINE__)
#define 		XCC_FUNC_D_EXEC						XLOG_DEBUG(nullptr, u8"[%s : %d] ----------", __XFUNCTION__, __XLINE__)
#define 		XCC_FUNC_D_LEAVE					XLOG_DEBUG(nullptr, u8"[%s : %d] >>>>>>>>>>", __XFUNCTION__, __XLINE__)

#define 		XCC_FUNC_I_ENTER					XLOG_INFO(nullptr, u8"[%s : %d] <<<<<<<<<<", __XFUNCTION__, __XLINE__)
#define 		XCC_FUNC_I_EXEC						XLOG_INFO(nullptr, u8"[%s : %d] ----------", __XFUNCTION__, __XLINE__)
#define 		XCC_FUNC_I_LEAVE					XLOG_INFO(nullptr, u8"[%s : %d] >>>>>>>>>>", __XFUNCTION__, __XLINE__)

#define 		XCC_FUNC_W_ENTER					XLOG_WARNING(nullptr, u8"[%s : %d] <<<<<<<<<<", __XFUNCTION__, __XLINE__)
#define 		XCC_FUNC_W_EXEC						XLOG_WARNING(nullptr, u8"[%s : %d] ----------", __XFUNCTION__, __XLINE__)
#define 		XCC_FUNC_W_LEAVE					XLOG_WARNING(nullptr, u8"[%s : %d] >>>>>>>>>>", __XFUNCTION__, __XLINE__)

#define 		XCC_FUNC_E_ENTER					XLOG_ERROR(nullptr, u8"[%s : %d] <<<<<<<<<<", __XFUNCTION__, __XLINE__)
#define 		XCC_FUNC_E_EXEC						XLOG_ERROR(nullptr, u8"[%s : %d] ----------", __XFUNCTION__, __XLINE__)
#define 		XCC_FUNC_E_LEAVE					XLOG_ERROR(nullptr, u8"[%s : %d] >>>>>>>>>>", __XFUNCTION__, __XLINE__)

#define 		XCC_FUNC_F_ENTER					XLOG_FATAL(nullptr, u8"[%s : %d] <<<<<<<<<<", __XFUNCTION__, __XLINE__)
#define 		XCC_FUNC_F_EXEC						XLOG_FATAL(nullptr, u8"[%s : %d] ----------", __XFUNCTION__, __XLINE__)
#define 		XCC_FUNC_F_LEAVE					XLOG_FATAL(nullptr, u8"[%s : %d] >>>>>>>>>>", __XFUNCTION__, __XLINE__)



XCC_CXX_EXTERN_END

#endif
