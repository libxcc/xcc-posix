#ifndef			_XCC_POSIX_SOCKET_H_
#define			_XCC_POSIX_SOCKET_H_

#include <xcc-posix/header.h>
#if !defined(XCC_SYSTEM_WINDOWS)
#include <netinet/in.h>
#include <poll.h>
#endif

XCC_CXX_EXTERN_BEGIN


// 套接字类型定义
#if defined(XCC_SYSTEM_WINDOWS)
typedef				SOCKET				x_socket_t;
#else
typedef				int 				x_socket_t;
#endif
#if defined(XCC_SYSTEM_WINDOWS)
typedef				unsigned long int		nfds_t;
#if !defined(_NSIG_WORDS)
#define				_NSIG_WORDS			2
#endif
typedef struct {
	unsigned long		sig[_NSIG_WORDS];
}sigset_t;
#else
#define INVALID_SOCKET		((x_socket_t)(-1))
#define SOCKET_ERROR		(-1)
#endif
#define X_INVALID_SOCKET	((x_socket_t)(-1))
#define X_SOCKET_ERROR		(-1)

#define	X_SOCKET_SHUT_RECV	(0)
#define	X_SOCKET_SHUT_WRITE	(1)
#define	X_SOCKET_SHUT_BOTH	(2)



// posix : gethostbyname
_XPOSIXAPI_ struct hostent* __xcall__ x_socket_get_host_by_name(const char* _Name);

// posix : gethostname
_XPOSIXAPI_ int __xcall__ x_socket_get_host_name(char* _Name, size_t _Length);

// posix : sethostname
_XPOSIXAPI_ int __xcall__ x_socket_set_host_name(const char* _Name, size_t _Length);

// posix : socket
_XPOSIXAPI_ x_socket_t __xcall__ x_socket_open(int _Family, int _Type, int _Protocol);

// posix : connect
_XPOSIXAPI_ int __xcall__ x_socket_connect(x_socket_t _Socket, const struct sockaddr* _Address, socklen_t _Length);

// posix : accept
_XPOSIXAPI_ x_socket_t __xcall__ x_socket_accept(x_socket_t _Socket, struct sockaddr* _Address, socklen_t* _Length);

// posix : bind
_XPOSIXAPI_ int __xcall__ x_socket_bind(x_socket_t _Socket, const struct sockaddr* _Address, socklen_t _Length);

// posix : close
_XPOSIXAPI_ int __xcall__ x_socket_close(x_socket_t _Socket);

// posix : getpeername
_XPOSIXAPI_ int __xcall__ x_socket_get_peer_name(x_socket_t _Socket, struct sockaddr* _Address, socklen_t* _Length);

// posix : getsockname
_XPOSIXAPI_ int __xcall__ x_socket_get_sock_name(x_socket_t _Socket, struct sockaddr* _Address, socklen_t* _Length);

// posix : getsockopt
_XPOSIXAPI_ int __xcall__ x_socket_get_opt(x_socket_t _Socket, int _Level, int _OptName, void* _OptValue, socklen_t* _OptLength);

// posix : setsockopt
_XPOSIXAPI_ int __xcall__ x_socket_set_opt(x_socket_t _Socket, int level, int _OptName, const void* _OptValue, socklen_t _OptLength);

// posix : inet_addr
_XPOSIXAPI_ struct in_addr __xcall__ x_socket_inet_addr(const char* _CP);

// posix : inet_ntoa
_XPOSIXAPI_ char* __xcall__ x_socket_inet_ntoa(struct in_addr _IN);

// posix : listen
_XPOSIXAPI_ int __xcall__ x_socket_listen(x_socket_t _Socket, int _Backlog);

// posix : recv
_XPOSIXAPI_ int __xcall__ x_socket_recv(x_socket_t _Socket, void* _Buffer, int _Length, int _Flags);

// posix : recvfrom
_XPOSIXAPI_ int __xcall__ x_socket_recvfrom(x_socket_t _Socket, void* _Buffer, int _Length, int _Flags, struct sockaddr* _From, socklen_t* _FromLen);

// posix : send
_XPOSIXAPI_ int __xcall__ x_socket_send(x_socket_t _Socket, const void* _Buffer, int _Length, int _Flags);

// posix : sendto
_XPOSIXAPI_ int __xcall__ x_socket_sendto(x_socket_t _Socket, const void* _Buffer, int _Length, int _Flags, const struct sockaddr* _To, socklen_t _ToLen);

// posix : shutdown
_XPOSIXAPI_ int __xcall__ x_socket_shutdown(x_socket_t _Socket, int _Now);

// posix : select
_XPOSIXAPI_ int __xcall__ x_socket_select(int _Fds, fd_set* _ReadFds, fd_set* _WriteFds, fd_set* _ExceptFds, struct timeval* _Timeout);

// posix : poll
_XPOSIXAPI_ int __xcall__ x_socket_poll(struct pollfd _Fds[], nfds_t _Count, int _Timeout);

// posix : ppoll
_XPOSIXAPI_ int __xcall__ x_socket_ppoll(struct pollfd* _Fds, nfds_t _Count, const struct timespec* _Timeout, const sigset_t* _SigMask);



// 检查套接字是否连接，已连接返回1，未连接返回0，异常返回-1。
_XPOSIXAPI_ int __xcall__ x_socket_is_connected(x_socket_t _Socket, unsigned int _Timeout);

// 检查套接字是否断开，已断开返回1，未断开返回0，异常返回-1。
_XPOSIXAPI_ int __xcall__ x_socket_is_disconnected(x_socket_t _Socket, unsigned int _Timeout);

// 检查套接字是否监听中，已监听返回1，未监听返回0，异常返回-1。
_XPOSIXAPI_ int __xcall__ x_socket_is_listen(const char* _Address, x_uint16_t _Port, unsigned int _Timeout);

// 检查socket是否可读，可读返回1，不可读返回0，异常返回-1。
_XPOSIXAPI_ int __xcall__ x_socket_is_readable(x_socket_t _Socket, unsigned int _Timeout);

// 检查socket是否可写，可写返回1，不可写返回0，异常返回-1。
_XPOSIXAPI_ int __xcall__ x_socket_is_writable(x_socket_t _Socket, unsigned int _Timeout);

// 检查套接字状态。 三种状态至少要传入一个值
_XPOSIXAPI_ bool __xcall__ x_socket_select_status(x_socket_t _Socket, bool* _Readable, bool* _Writable, bool* _Except, unsigned int _Timeout);



// socket : Set socket heartbeat
_XPOSIXAPI_ int __xcall__ x_socket_set_keepalive(x_socket_t _Socket, bool _KeepAlive, int _KeepIdle, int _KeepInterval, int _KeepCount);



// Get a list of local IP addresses
_XPOSIXAPI_ int __xcall__ x_socket_local_ip_list(char*** _IPAddressListPtr, x_size_t* _Size);

// Free list of local IP addresses
_XPOSIXAPI_ void __xcall__ x_socket_free_ip_list(char** _IPAddressListPtr);

// Translate IP address from fabric
_XPOSIXAPI_ char* __xcall__ x_socket_address_to_string(const struct sockaddr* _Address);



// posix : 接收所有数据
_XPOSIXAPI_ int __xcall__ x_socket_recv_all(x_socket_t _Socket, void* _Buffer, int _Length, int _Flags);

// posix : 接收所有数据
_XPOSIXAPI_ int __xcall__ x_socket_recvfrom_all(x_socket_t _Socket, void* _Buffer, int _Length, int _Flags, struct sockaddr* _From, socklen_t* _FromLen);

// posix : 发送所有数据
_XPOSIXAPI_ int __xcall__ x_socket_send_all(x_socket_t _Socket, const void* _Buffer, int _Length, int _Flags);

// posix : 发送所有数据
_XPOSIXAPI_ int __xcall__ x_socket_sendto_all(x_socket_t _Socket, const void* _Buffer, int _Length, int _Flags, const struct sockaddr* _To, socklen_t _ToLen);



// 在两个套接字之间传输数据
_XPOSIXAPI_ int __xcall__ x_socket_transfer(x_socket_t _Socket1, x_socket_t _Socket2);



XCC_CXX_EXTERN_END

#endif
