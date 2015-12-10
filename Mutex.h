#ifndef _MUTEX_H_
#define _MUTEX_H_

#include <pthread.h>

/**
 * @class Null_Mutex
 */
class Null_Mutex
{
public:
    Null_Mutex() {}

    ~Null_Mutex() {}

public:
    inline int acquire()
    {
        return 0;
    }

    inline int try_acquire()
    {
        return 0;
    }

    inline int release()
    {
        return 0;
    }
};

/**
 * @class Thread_Mutex
 */

class Thread_Mutex
{
public:
    Thread_Mutex();

    ~Thread_Mutex();

public:
    /// acquire the mutex
    int acquire();

    /// try to acquire the mutex
    int try_acquire();

    /// release the mutex
    int release();

    /// return the underlying lock
    const pthread_mutex_t &lock() const;
private:
    pthread_mutexattr_t _attr;
    pthread_mutex_t _mutex;
};

#include "Mutex.inl"

#endif
