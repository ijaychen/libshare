#ifndef _SINGLETON_H_
#define _SINGLETON_H_

#include <assert.h>

/**
 * @class Singleton
 */
template<typename T>
class Singleton
{
protected:
    Singleton()
    {
        assert(!_instance);
        _instance = static_cast<T *>(this);
    }

public:
    ~Singleton()
    {
        assert(_instance);
        _instance = 0;
    }

public:
    static void create_instance()
    {
        new T();
    }

    static void destroy_instance()
    {
        assert(_instance);
        delete _instance;
    }

    static T *instance()
    {
        assert(_instance);
        return _instance;
    }

private:
    static T *_instance;
};

/// instance initialization
template<typename T> T *Singleton<T>::_instance = 0;

#endif
