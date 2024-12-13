#include <xcc-posix/time.h>
#include <xcc-posix/memory.h>
#include <xcc-posix/socket.h>
#if !defined(XCC_SYSTEM_ANDROID)
#include <sys/timeb.h>
#endif
#if !defined(XCC_SYSTEM_WINDOWS)
#include <sys/time.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#endif



// 高精度计时结构
typedef struct XCC_TIME_HPT_CONTEXT
{
#if defined(XCC_SYSTEM_WINDOWS)
	LARGE_INTEGER		time_begin;			// 开始时间
	LARGE_INTEGER		time_end;			// 结束时间
	LARGE_INTEGER		time_cpu;			// CPU时间
#else
	struct timeval		time_begin;			// 开始时间
	struct timeval		time_end;			// 结束时间
#endif
}XCC_TIME_HPT_CONTEXT;



// posix - srand
_XPOSIXAPI_ void __xcall__ x_posix_srand(unsigned int _Seed)
{
	srand(_Seed);
}

// posix - rand
_XPOSIXAPI_ int __xcall__ x_posix_rand(void)
{
	return rand();
}

// posix - time
_XPOSIXAPI_ time_t __xcall__ x_posix_time(time_t* _Seconds)
{
	return time(_Seconds);
}

// posix - sleep
_XPOSIXAPI_ unsigned int __xcall__ x_posix_sleep(unsigned int _Seconds)
{
#if defined(XCC_SYSTEM_WINDOWS)
	return x_posix_msleep(_Seconds * 1000);
#else
	return sleep(_Seconds);
#endif
}

// posix - msleep
_XPOSIXAPI_ unsigned int __xcall__ x_posix_msleep(unsigned int _Milliseconds)
{
#if defined(XCC_SYSTEM_WINDOWS)
	Sleep(_Milliseconds);
	return 0;
#else
	return usleep(_Milliseconds * 1000) / 1000;
#endif
}

// posix - usleep
_XPOSIXAPI_ unsigned int __xcall__ x_posix_usleep(unsigned int _Microseconds)
{
#if defined(XCC_SYSTEM_WINDOWS)
	LARGE_INTEGER	vInterval;
	vInterval.QuadPart = -(10 * (int64_t)(_Microseconds));

	HANDLE 		vTimer = CreateWaitableTimerA(NULL, TRUE, NULL);
	SetWaitableTimer(vTimer, &vInterval, 0, NULL, NULL, 0);
	WaitForSingleObject(vTimer, INFINITE);
	CloseHandle(vTimer);
	return 0;
#else
	return usleep(_Microseconds);
#endif
}



// 获取当前系统时间的总秒数
_XPOSIXAPI_ x_time_type __xcall__ x_time_system_second()
{
	x_time_type		vSecond = 0;
#if defined(XCC_SYSTEM_WINDOWS)
	struct timeb		vRawtime;
	ftime(&vRawtime);
	vSecond = vRawtime.time;
#else
	struct timespec		vTimeSpec;
	clock_gettime(CLOCK_REALTIME, &vTimeSpec);
	vSecond = vTimeSpec.tv_sec;
#endif
	return vSecond;
}

// 获取当前系统时间的总毫秒数
_XPOSIXAPI_ x_time_type __xcall__ x_time_system_millisecond()
{
	x_time_type		vMillisecond = 0;
#if defined(XCC_SYSTEM_WINDOWS)
	struct timeb		vRawtime;
	ftime(&vRawtime);
	vMillisecond = vRawtime.time * 1000LL + vRawtime.millitm;
#else
	struct timespec		vTimeSpec;
	clock_gettime(CLOCK_REALTIME, &vTimeSpec);
	vMillisecond = vTimeSpec.tv_sec * 1000;
	vMillisecond += (vTimeSpec.tv_nsec / 1000000);
#endif
	return vMillisecond;
}

// 获取当前系统时间的总微秒数
_XPOSIXAPI_ x_time_type __xcall__ x_time_system_microsecond()
{
	x_time_type		vMicrosecond = 0;
#if defined(XCC_SYSTEM_WINDOWS)
	// Time from 0:0:0:000 on January 1, 1601 to 0:0:0:000 on January 1, 1970 (unit: 100ns)
#define			TIME_OFFSET_1601_TO_1970   (116444736000000000LL)

	FILETIME		vFileTime;
	LARGE_INTEGER		vLarge;
	GetSystemTimeAsFileTime(&vFileTime);
	vLarge.LowPart = vFileTime.dwLowDateTime;
	vLarge.HighPart = (LONG)vFileTime.dwHighDateTime;
	// Microseconds from 0:0:0:000 on January 1, 1970 (UTC time)
	vMicrosecond = (vLarge.QuadPart - TIME_OFFSET_1601_TO_1970) / 10;
#else
	struct timespec		vTimeSpec;
	clock_gettime(CLOCK_REALTIME, &vTimeSpec);
	vMicrosecond = vTimeSpec.tv_sec * 1000000;
	vMicrosecond += (vTimeSpec.tv_nsec / 1000);
#endif
	return vMicrosecond;
}



// 高精度计时器: 创建
_XPOSIXAPI_ HANDLE __xcall__ x_time_hpt_new()
{
	XCC_TIME_HPT_CONTEXT*	vContext = (XCC_TIME_HPT_CONTEXT*)x_posix_malloc(sizeof(XCC_TIME_HPT_CONTEXT));
	if (vContext)
	{
		x_time_hpt_reset(vContext);
	}
	return vContext;
}

// 高精度计时器: 重置
_XPOSIXAPI_ void __xcall__ x_time_hpt_reset(HANDLE _Handle)
{
	XCC_TIME_HPT_CONTEXT*		vContext = (XCC_TIME_HPT_CONTEXT*)_Handle;
	if (vContext)
	{
		x_posix_memset(vContext, 0, sizeof(XCC_TIME_HPT_CONTEXT));
#if defined(XCC_SYSTEM_WINDOWS)
		QueryPerformanceFrequency(&(vContext->time_cpu));
		QueryPerformanceCounter(&(vContext->time_begin));
#else
		gettimeofday(&(vContext->time_begin), NULL);
#endif
	}
}

// 高精度计时器: 计算
_XPOSIXAPI_ x_time_type __xcall__ x_time_hpt_calc(HANDLE _Handle)
{
	x_time_type			vDifference = 0;
	XCC_TIME_HPT_CONTEXT*		vContext = (XCC_TIME_HPT_CONTEXT*)_Handle;
	if (vContext)
	{
#if defined(XCC_SYSTEM_WINDOWS)
		QueryPerformanceCounter(&(vContext->time_end));

		x_time_type		dbCpuTime = vContext->time_cpu.QuadPart;
		x_time_type		nTemp = vContext->time_end.QuadPart - vContext->time_begin.QuadPart;
		vDifference = nTemp * 1000 / dbCpuTime;
#else
		gettimeofday(&(vContext->time_end), NULL);
		x_time_type		vTvSec = vContext->time_end.tv_sec - vContext->time_begin.tv_sec;
		x_time_type		vTvUsec = vContext->time_end.tv_usec - vContext->time_begin.tv_usec;
		vDifference += vTvSec * 1000000 + vTvUsec;
#endif
	}

	// 返回微秒值
	return vDifference;
}

// 高精度计时器: 释放
_XPOSIXAPI_ x_time_type __xcall__ x_time_hpt_free(HANDLE _Handle)
{
	x_time_type			vDifference = x_time_hpt_calc(_Handle);
	x_posix_free((XCC_TIME_HPT_CONTEXT*)_Handle);
	return vDifference;
}



// NTP 请求包结构
typedef struct XCC_NTP_PACKET
{
	uint8_t			li_vn_mode;		// 控制和标识 NTP 数据包的状态
	uint8_t			stratum;		// 服务器的层级
	uint8_t			poll;			// 服务器的轮询间隔
	uint8_t			precision;		// 服务器时钟的精度（2 的幂表示的时间间隔，单位为秒）
	uint32_t		rootDelay;		// 客户端到参考时钟的总延迟时间（单位：秒）
	uint32_t		rootDispersion;		// 参考时钟的最大允许误差（单位：秒）
	uint32_t		referenceID;		// 参考时钟的标识符
	uint32_t		referenceTimestamp[2];	// 参考时间戳
	uint32_t		originateTimestamp[2];	// 客户端发送请求的时间戳
	uint32_t		receiveTimestamp[2];	// 服务器接收到请求的时间戳
	uint32_t		transmitTimestamp[2];	// 服务器响应时间戳
}XCC_NTP_PACKET;

// NTP - 请求授时中心的时间 - 秒
_XPOSIXAPI_ x_time_type __xcall__ x_time_ntp_sec(const char* _NtpUrl)
{
	return x_time_ntp_msec(_NtpUrl) / 1000000;
}

// NTP - 请求授时中心的时间 - 毫秒
_XPOSIXAPI_ x_time_type __xcall__ x_time_ntp_msec(const char* _NtpUrl)
{
	return x_time_ntp_usec(_NtpUrl) / 1000;
}

// NTP - 请求授时中心的时间 - 微秒
_XPOSIXAPI_ x_time_type __xcall__ x_time_ntp_usec(const char* _NtpUrl)
{
	if(NULL == _NtpUrl)
	{
		_NtpUrl = "ntp.ntsc.ac.cn";
	}

	// 准备服务器信息
	struct sockaddr_in	vSrvAddr;
	struct addrinfo		vDnsHints;
	struct addrinfo*	vDnsRes = NULL;
	memset(&vSrvAddr, 0, sizeof(struct sockaddr_in));
	memset(&vDnsHints, 0, sizeof(struct addrinfo));
	vDnsHints.ai_family = AF_INET;
	vDnsHints.ai_socktype = SOCK_DGRAM;
	int			vDnsStatus = getaddrinfo(_NtpUrl, NULL, &vDnsHints, &vDnsRes);
	if (0 != vDnsStatus)
	{
		return 0;
	}
	memcpy(&vSrvAddr, vDnsRes->ai_addr, vDnsRes->ai_addrlen);
	vSrvAddr.sin_family = AF_INET;
	vSrvAddr.sin_port = htons(123);
	freeaddrinfo(vDnsRes);

	// 定义套接字
	x_socket_t	vSocket = x_socket_open(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if(X_INVALID_SOCKET == vSocket)
	{
		return 0;
	}

	// 发送数据 - NTP请求数据包的第一个字节设置为0x1b（时钟同步模式）
	unsigned char	vDataNTP[48] = {0};
	vDataNTP[0] = 0x1B;
	if (X_SOCKET_ERROR == x_socket_sendto(vSocket, vDataNTP, sizeof(vDataNTP), 0, (struct sockaddr*)&vSrvAddr, sizeof(struct sockaddr_in)))
	{
		x_socket_close(vSocket);
		return 0;
	}

	// 接收来自服务器的响应数据包
	socklen_t		vSrvSize = sizeof(struct sockaddr_in);
	if (X_SOCKET_ERROR == x_socket_recvfrom(vSocket, vDataNTP, sizeof(vDataNTP), 0, (struct sockaddr*)&vSrvAddr, &vSrvSize))
	{
		x_socket_close(vSocket);
		return 0;
	}

	// 关闭套接字
	x_socket_close(vSocket);

	// 解析时间戳（从第40-47字节解析出秒和小数秒）
	// x_uint32_t		vTimeLeft = (vDataNTP[40] << 24) | (vDataNTP[41] << 16) | (vDataNTP[42] << 8) | vDataNTP[43];
	// x_uint32_t		vTimeRight = (vDataNTP[44] << 24) | (vDataNTP[45] << 16) | (vDataNTP[46] << 8) | vDataNTP[47];
	uint32_t		vTimeLeft = ntohl(*(uint32_t*)(vDataNTP + 40));
	uint32_t		vTimeRight = ntohl(*(uint32_t*)(vDataNTP + 44));

	// 转换为 Unix 时间戳（减去NTP时间戳的起始时间）
	static x_time_type	NTP_TIMESTAMP_DELTA = 2208988800ull;
	static double		NTP_CONVERT_BASE = 4294967296.0;
	x_time_type 		vNtpLeft = (x_time_type)vTimeLeft - NTP_TIMESTAMP_DELTA;
	x_time_type 		vNtpRight = (x_time_type)(vTimeRight / NTP_CONVERT_BASE * 1000000);
	x_time_type		vNtpUsec = vNtpLeft * 1000000 + vNtpRight;
	return vNtpUsec;
}
