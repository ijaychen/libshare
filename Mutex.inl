#ifndef _MUTEX_INL_
#define _MUTEX_INL_

#include "Mutex.h"

inline Thread_Mutex::Thread_Mutex()
{
    ::pthread_mutexattr_init (&_attr);
    ::pthread_mutexattr_settype (&_attr, PTHREAD_MUTEX_RECURSIVE_NP);
    ::pthread_mutex_init (&_mutex, &_attr);
}

inline Thread_Mutex::~Thread_Mutex()
{
    ::pthread_mutexattr_destroy (&_attr);
    ::pthread_mutex_destroy (&_mutex);
}

inline int Thread_Mutex::acquire()
{
    return ::pthread_mutex_lock (&_mutex) == 0 ? 0 : -1;
}

inline int Thread_Mutex::try_acquire()
{
    return ::pthread_mutex_trylock (&_mutex) == 0 ? 0 : -1;
}

inline int Thread_Mutex::release()
{
    return ::pthread_mutex_unlock (&_mutex) == 0 ? 0 : -1;
}

inline const pthread_mutex_t & Thread_Mutex::lock() const
{
    return this->_mutex;
}

#endif
