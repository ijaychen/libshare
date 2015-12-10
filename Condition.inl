#ifndef _CONDITION_INL_
#define _CONDITION_INL_

#include "Condition.h"

inline Condition::Condition(Thread_Mutex &mutex)
    : _external_mutex(&mutex)
{
}

inline Condition::~Condition()
{
}

inline int Condition::signal()
{
    return ::pthread_cond_signal (&_cond);
}

inline int Condition::broadcast()
{
    return ::pthread_cond_broadcast (&_cond);
}

inline int Condition::wait(int timeout)
{
	if(timeout < 0)
	{
		pthread_mutex_t mutex = _external_mutex->lock();
		return ::pthread_cond_wait(&_cond, &mutex);
	}
}

#endif
