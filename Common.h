#ifndef _ECL_COMMON_H_
#define _ECL_COMMON_H_

// platform macro
#if defined (_WIN32)
#   define ECL_WIN
#   define ECL_NET_IOCP
#else
#   define ECL_LINUX
#   define ECL_NET_EPOLL
#endif

// win32 version
#if defined(_WIN32) && !defined(_WIN32_WINNT)
#   define _WIN32_WINNT 0x502
#endif

// debug mode
#if defined (_DEBUG)
#   define ECL_DEBUG
#endif

// include related headers
#if defined (ECL_WIN)
#   include <stdio.h>
#   include <stdlib.h>
#   include <winsock2.h>
#   include <mswsock.h>
#   include <windows.h>
#   include <errno.h>
#else
#   include <stdio.h>
#   include <stdlib.h>
#   include <stdint.h>
#   include <sys/socket.h>
#   include <netinet/tcp.h>
#   include <netinet/in.h>
#   include <arpa/inet.h>
#   include <errno.h>
#endif

// integer types
#if defined(ECL_WIN)
    typedef __int8  int8;
    typedef __int16 int16;
    typedef __int32 int32;
    typedef __int64 int64;

    typedef unsigned __int8  uint8;
    typedef unsigned __int16 uint16;
    typedef unsigned __int32 uint32;
    typedef unsigned __int64 uint64;
#else
    typedef int8_t  int8;
    typedef int16_t int16;
    typedef int32_t int32;
    typedef int64_t int64;

    typedef uint8_t  uint8;
    typedef uint16_t uint16;
    typedef uint32_t uint32;
    typedef uint64_t uint64;
#endif

// net kernel
//#include "Net.h"

// 64bits stuff
#if defined (ECL_WIN)
#   define FMT_I64d  "%I64d"
#   define FMT_I64u  "%I64u"
#   define atoi64    _atoi64
#   define strtoui64 _strtoui64
#else
#   define FMT_I64d  "%lld"
#   define FMT_I64u  "%llu"
#   define atoi64    atoll
#   define strtoui64 strtoull
#endif

// crt fucking stuffs
#if defined (ECL_WIN)
#   define snprintf _snprintf
#   define strdup   _strdup
#   define stricmp  _stricmp
#   define strnicmp _strnicmp
#   define strlwr   _strlwr
#   define strupr   _strupr
#   define fileno   _fileno
#else
#   define stricmp  strcasecmp
#   define strnicmp strncasecmp
#endif

// UNUSED_ARG
template <typename T> inline void UNUSED_ARG (const T&) {}

// ECL_Config
//#include "ECL_Config.h"

// ECL_Macros
//#include "ECL_Macros.h"

#endif
