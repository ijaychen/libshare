#ifndef _TIMER_H_
#define _TIMER_H_

#include "Common.h"
#include <sys/time.h>

inline uint64 now64()
{
    struct timeval tv;
    gettimeofday(&tv, 0);
    return (uint64)tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

inline uint32 now()
{
    return now64();
}

inline uint32 tick()
{
    return now64();
}

#endif
