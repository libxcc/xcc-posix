#include <xcc-posix/socket.h>
#include <xcc-posix/string.h>
#include <xcc-posix/system.h>
#include <xcc-posix/memory.h>
#include <errno.h>
#if defined(XCC_SYSTEM_WINDOWS)
#include <mstcpip.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <netdb.h>
#endif



// posix - gethostbyname
_XPOSIXAPI_ struct hostent* __xcall__ x_socket_get_host_by_name(const char* _Name)
{
	return gethostbyname(_Name);
}

// posix - gethostname
_XPOSIXAPI_ int __xcall__ x_socket_get_host_name(char* _Name, size_t _Length)
{
#if defined(XCC_SYSTEM_WINDOWS)
	return gethostname(_Name, (int)_Length);
#else
	return gethostname(_Name, _Length);
#endif
}

// posix - sethostname
_XPOSIXAPI_ int __xcall__ x_socket_set_host_name(const char* _Name, size_t _Length)
{
#if defined(XCC_SYSTEM_WINDOWS)
	char		vNameA[MAX_COMPUTERNAME_LENGTH + 1];
	x_posix_memset(vNameA, 0, MAX_COMPUTERNAME_LENGTH + 1);
	x_posix_strncpy(vNameA, _Name, _Length > MAX_COMPUTERNAME_LENGTH ? MAX_COMPUTERNAME_LENGTH : _Length);

	// Applications using this function must have administrator rights.
	if(SetComputerNameA(vNameA))
	{
		return 0;
	}
	return x_system_get_last_error();
#else
	return sethostname(_Name, _Length);
#endif
}

// posix - socket
_XPOSIXAPI_ x_socket_t __xcall__ x_socket_open(int _Family, int _Type, int _Protocol)
{
	return socket(_Family, _Type, _Protocol);
}

// posix - connect
_XPOSIXAPI_ int __xcall__ x_socket_connect(x_socket_t _Socket, const struct sockaddr* _Address, socklen_t _Length)
{
	return connect(_Socket, _Address, _Length);
}

// posix - accept
_XPOSIXAPI_ x_socket_t __xcall__ x_socket_accept(x_socket_t _Socket, struct sockaddr* _Address, socklen_t* _Length)
{
	return accept(_Socket, _Address, _Length);
}

// posix - bind
_XPOSIXAPI_ int __xcall__ x_socket_bind(x_socket_t _Socket, const struct sockaddr* _Address, socklen_t _Length)
{
	return bind(_Socket, _Address, _Length);
}

// posix - close
_XPOSIXAPI_ int __xcall__ x_socket_close(x_socket_t _Socket)
{
#if defined(XCC_SYSTEM_WINDOWS)
	return closesocket(_Socket);
#else
	return close(_Socket);
#endif
}

// posix - getpeername
_XPOSIXAPI_ int __xcall__ x_socket_get_peer_name(x_socket_t _Socket, struct sockaddr* _Address, socklen_t* _Length)
{
	return getpeername(_Socket, _Address, _Length);
}

// posix - getsockname
_XPOSIXAPI_ int __xcall__ x_socket_get_sock_name(x_socket_t _Socket, struct sockaddr* _Address, socklen_t* _Length)
{
	return getsockname(_Socket, _Address, _Length);
}

// posix - getsockopt
_XPOSIXAPI_ int __xcall__ x_socket_get_opt(x_socket_t _Socket, int _Level, int _OptName, void* _OptValue, socklen_t* _OptLength)
{
#if defined(XCC_SYSTEM_WINDOWS)
	return getsockopt(_Socket, _Level, _OptName, (char*)_OptValue, _OptLength);
#else
	return getsockopt(_Socket, _Level, _OptName, _OptValue, _OptLength);
#endif
}

// posix - setsockopt
_XPOSIXAPI_ int __xcall__ x_socket_set_opt(x_socket_t _Socket, int _Level, int _OptName, const void* _OptValue, socklen_t _OptLength)
{
#if defined(XCC_SYSTEM_WINDOWS)
	return setsockopt(_Socket, _Level, _OptName, (const char*)_OptValue, _OptLength);
#else
	return setsockopt(_Socket, _Level, _OptName, _OptValue, _OptLength);
#endif
}

// posix - inet_addr
_XPOSIXAPI_ struct in_addr __xcall__ x_socket_inet_addr(const char* _CP)
{
	struct in_addr		vAddress;
	vAddress.s_addr = inet_addr(_CP);
	return vAddress;
}

// posix - inet_ntoa
_XPOSIXAPI_ char* __xcall__ x_socket_inet_ntoa(struct in_addr _IN)
{
	return inet_ntoa(_IN);
}

// posix - listen
_XPOSIXAPI_ int __xcall__ x_socket_listen(x_socket_t _Socket, int _Backlog)
{
	return listen(_Socket, _Backlog);
}

// posix - recv
_XPOSIXAPI_ int __xcall__ x_socket_recv(x_socket_t _Socket, void* _Buffer, int _Length, int _Flags)
{
#if defined(XCC_SYSTEM_WINDOWS)
	return recv(_Socket, (char*)_Buffer, _Length, _Flags);
#else
	return recv(_Socket, _Buffer, _Length, _Flags);
#endif
}

// posix - recvfrom
_XPOSIXAPI_ int __xcall__ x_socket_recvfrom(x_socket_t _Socket, void* _Buffer, int _Length, int _Flags, struct sockaddr* _From, socklen_t* _FromLen)
{
#if defined(XCC_SYSTEM_WINDOWS)
	return recvfrom(_Socket, (char*)_Buffer, _Length, _Flags, _From, _FromLen);
#else
	return recvfrom(_Socket, _Buffer, _Length, _Flags, _From, _FromLen);
#endif
}

// posix - send
_XPOSIXAPI_ int __xcall__ x_socket_send(x_socket_t _Socket, const void* _Buffer, int _Length, int _Flags)
{
#if defined(XCC_SYSTEM_WINDOWS)
	return send(_Socket, (const char*)_Buffer, _Length, _Flags);
#else
	return send(_Socket, _Buffer, _Length, _Flags);
#endif
}

// posix - sendto
_XPOSIXAPI_ int __xcall__ x_socket_sendto(x_socket_t _Socket, const void* _Buffer, int _Length, int _Flags, const struct sockaddr* _To, socklen_t _ToLen)
{
#if defined(XCC_SYSTEM_WINDOWS)
	return sendto(_Socket, (const char*)_Buffer, _Length, _Flags, _To, _ToLen);
#else
	return sendto(_Socket, _Buffer, _Length, _Flags, _To, _ToLen);
#endif
}

// posix - shutdown
_XPOSIXAPI_ int __xcall__ x_socket_shutdown(x_socket_t _Socket, int _Now)
{
	return shutdown(_Socket, _Now);
}

// posix - select
_XPOSIXAPI_ int __xcall__ x_socket_select(int _Fds, fd_set* _ReadFds, fd_set* _WriteFds, fd_set* _ExceptFds, struct timeval* _Timeout)
{
	return select(_Fds, _ReadFds, _WriteFds, _ExceptFds, _Timeout);
}

// posix - poll
_XPOSIXAPI_ int __xcall__ x_socket_poll(struct pollfd _Fds[], nfds_t _Count, int _Timeout)
{
#if defined(X_CMAKE_HAVE_POLL)
	return poll(_Fds, _Count, _Timeout);
#else
#if defined(XCC_SYSTEM_WINDOWS)
	return WSAPoll(_Fds, _Count, _Timeout);
#else
	return poll(_Fds, _Count, _Timeout);
#endif
#endif
}

// posix - ppoll
_XPOSIXAPI_ int __xcall__ x_socket_ppoll(struct pollfd* _Fds, nfds_t _Count, const struct timespec* _Timeout, const sigset_t* _SigMask)
{
#if defined(X_CMAKE_HAVE_PPOLL)
	return ppoll(_Fds, _Count, _Timeout, _SigMask);
#else
#if defined(X_CMAKE_HAVE_SIGPROCMASK)
	int		vReady = 0;
	sigset_t	vOrigMask;
	int		vMillisecond = (int)((_Timeout->tv_sec * 1000) + (_Timeout->tv_nsec / 1000000));

	sigprocmask(SIG_SETMASK, _SigMask, &vOrigMask);
	vReady = x_socket_poll(_Fds, _Count, vMillisecond);
	sigprocmask(SIG_SETMASK, &vOrigMask, NULL);

	return vReady;
#else
	XCC_UNUSED(_SigMask);

	int		vReady = 0;
	int		vMillisecond = (int)((_Timeout->tv_sec * 1000) + (_Timeout->tv_nsec / 1000000));

	vReady = x_socket_poll(_Fds, _Count, vMillisecond);

	return vReady;
#endif
#endif
}



// 检查套接字是否连接，已连接返回1，未连接返回0，异常返回-1。
_XPOSIXAPI_ int __xcall__ x_socket_is_connected(x_socket_t _Socket, unsigned int _Timeout)
{
	if(_Socket == X_INVALID_SOCKET)
	{
		return -1;
	}

	int		vSelect = x_socket_is_readable(_Socket, _Timeout);
	if(vSelect <= 0)
	{
		return vSelect;
	}

	char		vBuffer[1] = {0};
	int		vSync = x_socket_recv(_Socket, vBuffer, 1, MSG_PEEK);
	if (vSync > 0)
	{
		return 1;
	}
	if (vSync == X_SOCKET_ERROR && (errno == EWOULDBLOCK || errno == EINTR))
	{
		// 没有数据可供接收
		return 1;
	}
	// 如果连接已正常关闭，则返回值为零
	return 0;
}

// 检查套接字是否断开，已断开返回1，未断开返回0，异常返回-1。
_XPOSIXAPI_ int __xcall__ x_socket_is_disconnected(x_socket_t _Socket, unsigned int _Timeout)
{
	if(_Socket == SOCKET_ERROR)
	{
		return -1;
	}

	int		vStatus = x_socket_is_connected(_Socket, _Timeout);
	if(vStatus > 0)
	{
		vStatus = 0;
	}
	else if(vStatus == 0)
	{
		vStatus = 1;
	}
	return vStatus;
}

// 检查套接字是否监听中，已监听返回1，未监听返回0，异常返回-1。
_XPOSIXAPI_ int __xcall__ x_socket_is_listen(const char* _Address, x_uint16_t _Port, unsigned int _Timeout)
{
	if(_Address == NULL || _Port == 0)
	{
		return -1;
	}

	// 创建套接字
	x_socket_t	vSocket = X_INVALID_SOCKET;
	if(x_posix_strstr(_Address, ":"))
	{
		vSocket = x_socket_open(AF_INET6, SOCK_STREAM, 0);
	}
	else if(x_posix_strstr(_Address, "."))
	{
		vSocket = x_socket_open(AF_INET, SOCK_STREAM, 0);
	}
	else
	{
		return -1;
	}
	if(vSocket == X_INVALID_SOCKET)
	{
		return -1;
	}

	// 设置超时时间
	struct timeval tv;
	tv.tv_sec = _Timeout / 1000;
	tv.tv_usec = (_Timeout % 1000) * 1000;
	if (x_socket_set_opt(vSocket, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv)) < 0)
	{
		x_socket_close(vSocket);
		return -1;
	}
	if (x_socket_set_opt(vSocket, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)) < 0)
	{
		x_socket_close(vSocket);
		return -1;
	}

	// 连接到服务器
	if(x_posix_strstr(_Address, ":"))
	{
		struct sockaddr_in6	vAddress;
		vAddress.sin6_family = AF_INET6;
		vAddress.sin6_port = htons(_Port);
		if (inet_pton(AF_INET6, _Address, &(vAddress.sin6_addr)) <= 0)
		{
			x_socket_close(vSocket);
			return -1;
		}

		// 连接到服务器
		if (x_socket_connect(vSocket, (struct sockaddr*)&vAddress, sizeof(struct sockaddr_in6)) < 0)
		{
			x_socket_close(vSocket);
			return 0;
		}
	}
	else if(x_posix_strstr(_Address, "."))
	{
		struct sockaddr_in	vAddress;
		vAddress.sin_family = AF_INET;
		vAddress.sin_port = htons(_Port);
		if (inet_pton(AF_INET, _Address, &(vAddress.sin_addr)) <= 0)
		{
			x_socket_close(vSocket);
			return -1;
		}

		// 连接到服务器
		if (x_socket_connect(vSocket, (struct sockaddr*)&vAddress, sizeof(struct sockaddr_in)) < 0)
		{
			x_socket_close(vSocket);
			return 0;
		}
	}

	// 释放资源
	x_socket_close(vSocket);
	return 1;
}

// 检查socket是否可读，可读返回1，不可读返回0，异常返回-1。
_XPOSIXAPI_ int __xcall__ x_socket_is_readable(x_socket_t _Socket, unsigned int _Timeout)
{
	fd_set		vFDS_Read;
	fd_set		vFDS_Except;
	struct timeval	vTimeout;
	vTimeout.tv_sec = (long)(_Timeout / 1000);
	vTimeout.tv_usec = (long) ((_Timeout % 1000) * 1000);

	FD_ZERO(&vFDS_Read);
	FD_ZERO(&vFDS_Except);
	FD_SET(_Socket, &vFDS_Read);
	FD_SET(_Socket, &vFDS_Except);

	int		vSelect = select((int)_Socket + 1, &vFDS_Read, NULL, &vFDS_Except, &vTimeout);
	if(vSelect > 0)
	{
		if(FD_ISSET(_Socket, &vFDS_Except))
		{
			return -1;
		}
		else if(FD_ISSET(_Socket, &vFDS_Read))
		{
			return 1;
		}
		return 0;
	}
	return vSelect == 0 ? 0 : -1;
}

// 检查socket是否可写，可写返回1，不可写返回0，异常返回-1。
_XPOSIXAPI_ int __xcall__ x_socket_is_writable(x_socket_t _Socket, unsigned int _Timeout)
{
	fd_set		vFDS_Write;
	fd_set		vFDS_Except;
	struct timeval	vTimeout;
	vTimeout.tv_sec = (long)(_Timeout / 1000);
	vTimeout.tv_usec = (long) ((_Timeout % 1000) * 1000);

	FD_ZERO(&vFDS_Write);
	FD_ZERO(&vFDS_Except);
	FD_SET(_Socket, &vFDS_Write);
	FD_SET(_Socket, &vFDS_Except);

	int		vSelect = select((int)_Socket + 1, NULL, &vFDS_Write, &vFDS_Except, &vTimeout);
	if(vSelect > 0)
	{
		if(FD_ISSET(_Socket, &vFDS_Except))
		{
			return -1;
		}
		else if(FD_ISSET(_Socket, &vFDS_Write))
		{
			return 1;
		}
		return 0;
	}
	return vSelect == 0 ? 0 : -1;
}

// 检查套接字状态。 三种状态至少要传入一个值
_XPOSIXAPI_ bool __xcall__ x_socket_select_status(x_socket_t _Socket, bool* _Readable, bool* _Writable, bool* _Except, unsigned int _Timeout)
{
	fd_set		vFDS_Read;
	fd_set		vFDS_Write;
	fd_set		vFDS_Except;
	struct timeval	vTimeout;
	vTimeout.tv_sec = (long)(_Timeout / 1000);
	vTimeout.tv_usec = (long) ((_Timeout % 1000) * 1000);

	if(_Readable)
	{
		FD_ZERO(&vFDS_Read);
		FD_SET(_Socket, &vFDS_Read);
	}
	if(_Writable)
	{
		FD_ZERO(&vFDS_Write);
		FD_SET(_Socket, &vFDS_Write);
	}
	if(_Except)
	{
		FD_ZERO(&vFDS_Except);
		FD_SET(_Socket, &vFDS_Except);
	}

	bool		vFound = false;
	int		vSelect = select((int)_Socket + 1, _Readable ? &vFDS_Read : NULL, _Writable ? &vFDS_Write : NULL, _Except ? &vFDS_Except : NULL, &vTimeout);
	if(vSelect > 0)
	{
		if(_Readable)
		{
			*_Readable = FD_ISSET(_Socket, &vFDS_Read);
			vFound = true;
		}
		if(_Writable)
		{
			*_Writable = FD_ISSET(_Socket, &vFDS_Write);
			vFound = true;
		}
		if(_Except)
		{
			*_Except = FD_ISSET(_Socket, &vFDS_Except);
			vFound = true;
		}
		return vFound;
	}
	return false;
}



// socket : Set socket heartbeat
_XPOSIXAPI_ int __xcall__ x_socket_set_keepalive(x_socket_t _Socket, bool _KeepAlive, int _KeepIdle, int _KeepInterval, int _KeepCount)
{
#if defined(XCC_COMPILER_MSVC)
	XCC_UNUSED(_KeepCount);

	DWORD				vBytesReturn = 0;
	struct tcp_keepalive		vKA_Settings = {0};
	struct tcp_keepalive		vKA_Returned = {0};
	vKA_Settings.onoff = _KeepAlive ? 1 : 0;		// 是否开启KEEPALIVE
	vKA_Settings.keepalivetime = _KeepIdle;			// 多长毫秒时间触发Keepalive报文的发送
	vKA_Settings.keepaliveinterval = _KeepInterval;		// 多长毫秒时间没有回应触发下一次发送
	return WSAIoctl(_Socket, SIO_KEEPALIVE_VALS, &vKA_Settings, sizeof(struct tcp_keepalive), &vKA_Returned, sizeof(struct tcp_keepalive), &vBytesReturn, NULL, NULL);
#elif defined(XCC_COMPILER_LINUX)
	int		keepalive = _KeepAlive ? 1 : 0;		// 是否开启keepalive属性
	int		keepidle = _KeepIdle / 1000;		// 如该连接在 N 秒内没有任何数据往来,则进行探测
	int		keepinterval = _KeepInterval / 1000;	// 探测时发包的时间间隔为 N 秒
	int		keepcount = _KeepCount;			// 探测尝试的次数。如果第1次探测包就收到响应了,则后 N - 1 次的不再发。
	x_socket_set_opt(_Socket, SOL_SOCKET, SO_KEEPALIVE, &keepalive, sizeof(keepalive));
	x_socket_set_opt(_Socket, SOL_TCP, TCP_KEEPIDLE, &keepidle, sizeof(keepidle));
	x_socket_set_opt(_Socket, SOL_TCP, TCP_KEEPINTVL, &keepinterval, sizeof(keepinterval));
	x_socket_set_opt(_Socket, SOL_TCP, TCP_KEEPCNT, &keepcount, sizeof(keepcount));
	return 0;
#else
	XCC_UNUSED(_Socket);
	XCC_UNUSED(_KeepAlive);
	XCC_UNUSED(_KeepIdle);
	XCC_UNUSED(_KeepInterval);
	XCC_UNUSED(_KeepCount);
	return 0;
#endif
}



// Get a list of local IP addresses
_XPOSIXAPI_ int __xcall__ x_socket_local_ip_list(char*** _IPAddressListPtr, x_size_t* _Size)
{
	struct hostent*		vHostList = NULL;
	struct in_addr		vAddress;
	char*			vString = NULL;
	x_size_t 		vCount = 0;
	x_size_t 		vIndex = 0;
	char 			vHostName[XCC_PATH_MAX];
	int 			vSync = 0;

	if(_IPAddressListPtr == NULL || _Size == NULL)
	{
		return EINVAL;
	}

	vSync = x_socket_get_host_name(vHostName, XCC_PATH_MAX);
	if (0 != vSync)
	{
		return vSync;
	}

	vHostList = x_socket_get_host_by_name(vHostName);
	if (NULL == vHostList)
	{
		return x_system_get_last_error();
	}

	while(vHostList->h_addr_list[vCount])
	{
		++vCount;
	}
	*_IPAddressListPtr = (char**) x_posix_malloc(sizeof(char*) * (vCount + 1));
	*_Size = vCount;
	if(*_IPAddressListPtr == NULL)
	{
		return ENOMEM;
	}
	(*_IPAddressListPtr)[vCount] = NULL;

	for (vIndex = 0; vIndex < vCount; ++vIndex)
	{
		x_posix_memcpy(&(vAddress.s_addr), vHostList->h_addr_list[vIndex], vHostList->h_length);
		vString = x_socket_inet_ntoa(vAddress);
		(*_IPAddressListPtr)[vIndex] = x_posix_strdup(vString);
	}

	return 0;
}

// Free list of local IP addresses
_XPOSIXAPI_ void __xcall__ x_socket_free_ip_list(char** _IPAddressListPtr)
{
	x_size_t 	vSize = 0;
	while(_IPAddressListPtr && _IPAddressListPtr[vSize])
	{
		x_posix_free(_IPAddressListPtr[vSize]);
		++vSize;
	}
	x_posix_free(_IPAddressListPtr);
}

// Translate IP address from fabric
_XPOSIXAPI_ char* __xcall__ x_socket_address_to_string(const struct sockaddr* _Address)
{
	if(_Address->sa_family == AF_INET)
	{
		const struct sockaddr_in*	vIPv4 = (const struct sockaddr_in*)_Address;
#if defined(XCC_SYSTEM_WINDOWS)
		const char*			vAddress = inet_ntoa(vIPv4->sin_addr);
#else
		char				vAddress[1024] = {0};
		inet_ntop(AF_INET, vIPv4, vAddress, 1024);
#endif
		return x_posix_strdup(vAddress);
	}
	return x_posix_strdup("");
}



// posix - 接收所有数据
_XPOSIXAPI_ int __xcall__ x_socket_recv_all(x_socket_t _Socket, void* _Buffer, int _Length, int _Flags)
{
	char*		vBytes = (char*)_Buffer;
	int		vSyncSize = 0;
	while (vSyncSize < _Length)
	{
		int		vRecvSize = x_socket_recv(_Socket, vBytes + vSyncSize, _Length - vSyncSize, _Flags);
		if (vRecvSize <= 0)
		{
			break;
		}
		vSyncSize += vRecvSize;
	}
	return vSyncSize;
}

// posix - 接收所有数据
_XPOSIXAPI_ int __xcall__ x_socket_recvfrom_all(x_socket_t _Socket, void* _Buffer, int _Length, int _Flags, struct sockaddr* _From, socklen_t* _FromLen)
{
	char*		vBytes = (char*)_Buffer;
	int		vSyncSize = 0;
	while (vSyncSize < _Length)
	{
		int		vRecvSize = x_socket_recvfrom(_Socket, vBytes + vSyncSize, _Length - vSyncSize, _Flags, _From, _FromLen);
		if (vRecvSize <= 0)
		{
			break;
		}
		vSyncSize += vRecvSize;
	}
	return vSyncSize;
}

// posix - 发送所有数据
_XPOSIXAPI_ int __xcall__ x_socket_send_all(x_socket_t _Socket, const void* _Buffer, int _Length, int _Flags)
{
	const char*	vBytes = (const char*)_Buffer;
	int		vSyncSize = 0;
	while (vSyncSize < _Length)
	{
		int		vSendSize = x_socket_send(_Socket, vBytes + vSyncSize, _Length - vSyncSize, _Flags);
		if (vSendSize <= 0)
		{
			break;
		}
		vSyncSize += vSendSize;
	}
	return vSyncSize;
}

// posix - 发送所有数据
_XPOSIXAPI_ int __xcall__ x_socket_sendto_all(x_socket_t _Socket, const void* _Buffer, int _Length, int _Flags, const struct sockaddr* _To, socklen_t _ToLen)
{
	const char*	vBytes = (const char*)_Buffer;
	int		vSyncSize = 0;
	while (vSyncSize < _Length)
	{
		int		vSendSize = x_socket_sendto(_Socket, vBytes + vSyncSize, _Length - vSyncSize, _Flags, _To, _ToLen);
		if (vSendSize <= 0)
		{
			break;
		}
		vSyncSize += vSendSize;
	}
	return vSyncSize;
}



// 在两个套接字之间传输数据
_XPOSIXAPI_ int __xcall__ x_socket_transfer(x_socket_t _Socket1, x_socket_t _Socket2)
{
	if(_Socket1 == INVALID_SOCKET || _Socket2 == INVALID_SOCKET)
	{
		return EINVAL;
	}

	int		vError = 0;
	char 		vBuffer[XCC_SIZE_KB] = {0};
	int		vSocketMax = (int)(_Socket1 > _Socket2 ? _Socket1 : _Socket2);
	fd_set		vReadFds;
	fd_set 		vExceptFds;
	struct timeval	vTimeout;
	while(true)
	{
		FD_ZERO(&vReadFds);
		FD_SET(_Socket1, &vReadFds);
		FD_SET(_Socket2, &vReadFds);

		FD_ZERO(&vExceptFds);
		FD_SET(_Socket1, &vExceptFds);
		FD_SET(_Socket2, &vExceptFds);

		vTimeout.tv_sec = 1;
		vTimeout.tv_usec = 0;

		int		vSelect = x_socket_select(vSocketMax + 1, &vReadFds, NULL, &vExceptFds, &vTimeout);
		if(vSelect < 0)
		{
			// an error occurred
			vError = x_posix_errno();
			break;
		}
		else if(vSelect == 0)
		{
			// Socket query timed out
			continue;
		}
		else
		{
			// socket exception
			if (FD_ISSET(_Socket1, &vExceptFds) || FD_ISSET(_Socket2, &vExceptFds))
			{
				vError = x_posix_errno();
				break;
			}

			// There are sockets to read
			if (FD_ISSET(_Socket1, &vReadFds))
			{
				int		vReadBytes = x_socket_recv(_Socket1, vBuffer, XCC_SIZE_KB, 0);
				if(vReadBytes < 0)
				{
					// Failed to receive
					vError = x_posix_errno();
					break;
				}
				else if(vReadBytes == 0)
				{
					// The peer socket is closed
					break;
				}

				int		vSent = 0;
				while (vSent < vReadBytes)
				{
					int		vSendBytes = x_socket_send(_Socket2, vBuffer + vSent, vReadBytes - vSent, 0);
					if (vSendBytes <= 0)
					{
						// Failed to send
						vError = x_posix_errno();
						break;
					}
					vSent += vSendBytes;
				}
			}
			if (FD_ISSET(_Socket2, &vReadFds))
			{
				int		vReadBytes = x_socket_recv(_Socket2, vBuffer, XCC_SIZE_KB, 0);
				if(vReadBytes < 0)
				{
					// Failed to receive
					vError = x_posix_errno();
					break;
				}
				else if(vReadBytes == 0)
				{
					// The peer socket is closed
					break;
				}
				int		vSent = 0;
				while (vSent < vReadBytes)
				{
					int		vSendBytes = x_socket_send(_Socket1, vBuffer + vSent, vReadBytes - vSent, 0);
					if (vSendBytes <= 0)
					{
						// Failed to send
						vError = x_posix_errno();
						break;
					}
					vSent += vSendBytes;
				}
			}
		}
	}

	return vError;
}
