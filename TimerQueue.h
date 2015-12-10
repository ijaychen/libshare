#ifndef _TIMER_QUEUE_H_
#define _TIMER_QUEUE_H_

#include <tr1/unordered_map>
//#include <unordered_map>

#include "Common.h"
#include "PriorityQueue.h"
#include "Callback.h"
#include "Mutex.h"
#include "Guard.h"
#include "Timer.h"


using namespace std::tr1;

/**
 * @class Timer
 */
class Timer : public PQNode<Timer>
{
public:
    Timer(uint32 interval, Callback *cb, int16 periodic = 0)
        : _timer_id(0)
        , _interval(interval)
        , _due_time(now64() + _interval)
        , _cb(cb)
        , _periodic(periodic)
        , _expired(0)
    {}

    ~Timer()
    {
        if (_cb) delete _cb;
    }

public:
    /// PQ Node comparer
    int compare(const Timer *node) const
    {
        if (_due_time < node->_due_time)
            return -1;
        else if (_due_time > node->_due_time)
            return 1;
        else
            return 0;
    }

public:
    /// timer id. 0 if uninitialized
    uint32 _timer_id;

    /// timer interval in milliseconds
    uint32 _interval;

    /// due time to timeout
    uint64 _due_time;

    /// callback
    Callback *_cb;

    /// is periodic ?
    int16 _periodic;

    /// is expired ?
    int16 _expired;
};

/**
 * @class TimerQueue
 */
template<typename LOCK = Null_Mutex>
class TimerQueue
{
public:
    TimerQueue()
        : _timerid_seq(1)
    {}

    ~TimerQueue();

public:
    /**
     * @param periodic  whether the timer is periodic
     *
     * @retval uint32  added timer id
     */
    uint32 add_timer(uint32 interval, Callback *cb, int16 periodic = 0);

    /// cancel timer if found in timerqueue
    inline int cancel_timer(uint32 timer_id);

    /// change timer if found in timerqueue
    int change_timer(uint32 timer_id, uint32 interval, int16 periodic);

    /// get lefttime of a timer in milliseconds
    uint32 time_left(uint32 timer_id);

    /**
     * expire timers by "cur_time"
     *
     * this method will never block
     *
     * @retval  0 a timer is successfully expired
     * @retval -1 no timer is expired
     */
    int expire(uint64 cur_time);

private:
    /// cancel timer implementation
    int cancel_timer_i(uint32 timer_id, int remove_from_q = 1);

    /// find timer according to timer id
    Timer *find_timer(uint32 timer_id, int remove_from_map = 0);

private:
    PriorityQueue<Timer> _pq;

    typedef unordered_map<uint32, Timer *> TimerMap;
    TimerMap _timer_map;

    LOCK _lock;

    /// timer id sequence. start with 1
    uint32 _timerid_seq;
};

#include "TimerQueue.cpp"

#endif
