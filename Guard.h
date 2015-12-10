#ifndef _GUARD_H_
#define _GUARD_H_

#include "Common.h"

#include "Mutex.h"

/**
 * @class Guard
 */
template<typename LOCK>
class Guard
{
public:
    Guard(LOCK &l)
        : _lock(&l)
    {
        this->acquire();
    }

    ~Guard()
    {
        this->release();
    }

public:
    inline int acquire()
    {
        return _lock->acquire();
    }

    inline int try_acquire()
    {
        return _lock->try_acquire();
    }

    inline int release()
    {
        return _lock->release();
    }

private:
    LOCK *_lock;
};

/**
 * @class Guard<Null_Mutex>
 *
 * the specialization is used to speed up Null_Mutex Guard
 */
template<>
class Guard<Null_Mutex>
{
public:
    Guard(Null_Mutex &) {}

    ~Guard() {}

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
 * @class Read_Guard
 */
template<typename LOCK>
class Read_Guard
{
public:
    Read_Guard(LOCK &l)
        : _lock(&l)
    {
        this->acquire();
    }

    ~Read_Guard()
    {
        this->release();
    }

public:
    inline int acquire()
    {
        return _lock->acquire_read();
    }

    inline int try_acquire()
    {
        return _lock->try_acquire_read();
    }

    inline int release()
    {
        return _lock->release();
    }

private:
    LOCK *_lock;
};

/**
 * @class Write_Guard
 */
template<typename LOCK>
class Write_Guard
{
public:
    Write_Guard(LOCK &l)
        : _lock(&l)
    {
        this->acquire();
    }

    ~Write_Guard()
    {
        this->release();
    }

public:
    inline int acquire()
    {
        return _lock->acquire_write();
    }

    inline int try_acquire()
    {
        return _lock->try_acquire_write();
    }

    inline int release()
    {
        return _lock->release();
    }

private:
    LOCK *_lock;
};

#endif
