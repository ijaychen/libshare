#ifndef _NET_H_
#define _NET_H_

// net engine
#if defined (ECL_NET_IOCP) // IOCP

	#define SHUT_RD      SD_RECEIVE
	#define SHUT_WR      SD_SEND
	#define SHUT_RDWR    SD_BOTH

    typedef HANDLE SOCKET_HANDLE;
    typedef HANDLE SOCKET_FD;

	#define INVALID_SOCKET_FD     INVALID_HANDLE_VALUE
	#define INVALID_SOCKET_HANDLE INVALID_HANDLE_VALUE

	#define SOCKET_FD_FROM_HANDLE(h) h

#elif defined (ECL_NET_EPOLL) // EPOLL

	#include "Net_Epoll.h"

    typedef hsocket_t *SOCKET_HANDLE;
    typedef int        SOCKET_FD;

	#define INVALID_SOCKET_FD     -1
	#define INVALID_SOCKET_HANDLE 0

	#define SOCKET_FD_FROM_HANDLE(h) h->fd

#else
    // not supported
#endif // end of net engine

#endif
