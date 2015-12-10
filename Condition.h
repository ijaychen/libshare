#ifndef _CONDITION_H_
#define _CONDITION_H_

#include "Common.h"

#include <pthread.h>
#include "Mutex.h"
/**
 * @class Condition
 */
class Condition
{
public:
    Condition(Thread_Mutex &mutex);

    ~Condition();

public:
    /// external mutex MUST be held before calling these members
    int wait(int timeout = -1);

    int signal();

    int broadcast();

private:
    Thread_Mutex *_external_mutex;
    pthread_cond_t _cond;
};

#include "Condition.inl"

#endif
