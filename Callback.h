#ifndef _CALLBACK_H_
#define _CALLBACK_H_

/// forward declarations
template<typename T>
class CallbackP0;

template<typename T,typename P1>
class CallbackP1;

template<typename T,typename P1,typename P2>
class CallbackP2;

template<typename T,typename P1,typename P2,typename P3>
class CallbackP3;

template<typename T,typename P1,typename P2,typename P3,typename P4>
class CallbackP4;

template<typename T,typename P1,typename P2,typename P3,typename P4,typename P5>
class CallbackP5;

template<typename T,typename P1,typename P2,typename P3,typename P4,typename P5,typename P6>
class CallbackP6;

/**
 * @class Callback
 *
 * this is Callback base class
 */
class Callback
{
protected:
    Callback() {}

public:
    virtual ~Callback() {}

public:
    virtual void run() = 0;

/// static bind methods
public:
    template<typename T>
    inline static Callback *bind(T *obj,
                                 void (T::*m)())
    {
        return new CallbackP0<T>(obj, m);
    }

    template<typename T,typename P1>
    inline static Callback *bind(T *obj,
                                 void (T::*m)(P1),
                                 P1 p1)
    {
        return new CallbackP1<T,P1>(obj, m, p1);
    }

    template<typename T,typename P1,typename P2>
    inline static Callback *bind(T *obj,
                                 void (T::*m)(P1,P2),
                                 P1 p1,
                                 P2 p2)
    {
        return new CallbackP2<T,P1,P2>(obj, m, p1, p2);
    }

    template<typename T,typename P1,typename P2,typename P3>
    inline static Callback *bind(T *obj,
                                 void (T::*m)(P1,P2,P3),
                                 P1 p1,
                                 P2 p2,
                                 P3 p3)
    {
        return new CallbackP3<T,P1,P2,P3>(obj, m, p1, p2, p3);
    }

    template<typename T,typename P1,typename P2,typename P3,typename P4>
    inline static Callback *bind(T *obj,
                                 void (T::*m)(P1,P2,P3,P4),
                                 P1 p1,
                                 P2 p2,
                                 P3 p3,
                                 P4 p4)
    {
        return new CallbackP4<T,P1,P2,P3,P4>(obj, m, p1, p2, p3, p4);
    }

    template<typename T,typename P1,typename P2,typename P3,typename P4,typename P5>
    inline static Callback *bind(T *obj,
                                 void (T::*m)(P1,P2,P3,P4,P5),
                                 P1 p1,
                                 P2 p2,
                                 P3 p3,
                                 P4 p4,
                                 P5 p5)
    {
        return new CallbackP5<T,P1,P2,P3,P4,P5>(obj, m, p1, p2, p3, p4, p5);
    }

    template<typename T,typename P1,typename P2,typename P3,typename P4,typename P5, typename P6>
    inline static Callback *bind(T *obj,
                                 void (T::*m)(P1,P2,P3,P4,P5,P6),
                                 P1 p1,
                                 P2 p2,
                                 P3 p3,
                                 P4 p4,
                                 P5 p5,
                                 P6 p6)
    {
        return new CallbackP6<T,P1,P2,P3,P4,P5,P6>(obj, m, p1, p2, p3, p4, p5, p6);
    }
};

/**
 * @class CallbackP0
 *
 * Callback with 0 parameter
 */
template<typename T>
class CallbackP0 : public Callback
{
public:
    typedef void (T::*M)();

    CallbackP0(T *obj,
               M m)
               :
               _obj(obj),
               _m(m)
    {}

public:
    void run()
    {
        (_obj->*_m)();
    }

private:
    T *_obj;
    M _m;
};

/**
 * @class CallbackP1
 *
 * Callback with 1 parameters
 */
template<typename T,typename P1>
class CallbackP1 : public Callback
{
public:
    typedef void (T::*M)(P1);

    CallbackP1(T *obj,
               M m,
               P1 p1)
               :
               _obj(obj),
               _m(m),
               _p1(p1)
    {}

public:
    void run()
    {
        (_obj->*_m)(_p1);
    }

private:
    T *_obj;
    M _m;
    P1 _p1;
};

/**
 * @class CallbackP2
 *
 * Callback with 2 parameters
 */
template<typename T,typename P1,typename P2>
class CallbackP2 : public Callback
{
public:
    typedef void (T::*M)(P1,P2);

    CallbackP2(T *obj,
               M m,
               P1 p1,
               P2 p2)
               :
               _obj(obj),
               _m(m),
               _p1(p1),
               _p2(p2)
    {}

public:
    void run()
    {
        (_obj->*_m)(_p1, _p2);
    }

private:
    T *_obj;
    M _m;
    P1 _p1;
    P2 _p2;
};

/**
 * @class CallbackP3
 *
 * Callback with 3 parameters
 */
template<typename T,typename P1,typename P2,typename P3>
class CallbackP3 : public Callback
{
public:
    typedef void (T::*M)(P1,P2,P3);

    CallbackP3(T *obj,
               M m,
               P1 p1,
               P2 p2,
               P3 p3)
               :
               _obj(obj),
               _m(m),
               _p1(p1),
               _p2(p2),
               _p3(p3)
    {}

public:
    void run()
    {
        (_obj->*_m)(_p1, _p2, _p3);
    }

private:
    T *_obj;
    M _m;
    P1 _p1;
    P2 _p2;
    P3 _p3;
};

/**
 * @class CallbackP4
 *
 * Callback with 4 parameters
 */
template<typename T,typename P1,typename P2,typename P3,typename P4>
class CallbackP4 : public Callback
{
public:
    typedef void (T::*M)(P1,P2,P3,P4);

    CallbackP4(T *obj,
               M m,
               P1 p1,
               P2 p2,
               P3 p3,
               P4 p4)
               :
               _obj(obj),
               _m(m),
               _p1(p1),
               _p2(p2),
               _p3(p3),
               _p4(p4)
    {}

public:
    void run()
    {
        (_obj->*_m)(_p1, _p2, _p3, _p4);
    }

private:
    T *_obj;
    M _m;
    P1 _p1;
    P2 _p2;
    P3 _p3;
    P4 _p4;
};

/**
 * @class CallbackP5
 *
 * Callback with 5 parameters
 */
template<typename T,typename P1,typename P2,typename P3,typename P4,typename P5>
class CallbackP5 : public Callback
{
public:
    typedef void (T::*M)(P1,P2,P3,P4,P5);

    CallbackP5(T *obj,
               M m,
               P1 p1,
               P2 p2,
               P3 p3,
               P4 p4,
               P5 p5)
               :
               _obj(obj),
               _m(m),
               _p1(p1),
               _p2(p2),
               _p3(p3),
               _p4(p4),
               _p5(p5)
    {}

public:
    void run()
    {
        (_obj->*_m)(_p1, _p2, _p3, _p4, _p5);
    }

private:
    T *_obj;
    M _m;
    P1 _p1;
    P2 _p2;
    P3 _p3;
    P4 _p4;
    P5 _p5;
};

/**
 * @class CallbackP6
 *
 * Callback with 6 parameters
 */
template<typename T,typename P1,typename P2,typename P3,typename P4,typename P5,typename P6>
class CallbackP6 : public Callback
{
public:
    typedef void (T::*M)(P1,P2,P3,P4,P5,P6);

    CallbackP6(T *obj,
               M m,
               P1 p1,
               P2 p2,
               P3 p3,
               P4 p4,
               P5 p5,
               P6 p6)
               :
               _obj(obj),
               _m(m),
               _p1(p1),
               _p2(p2),
               _p3(p3),
               _p4(p4),
               _p5(p5),
               _p6(p6)
    {}

public:
    void run()
    {
        (_obj->*_m)(_p1, _p2, _p3, _p4, _p5, _p6);
    }

private:
    T *_obj;
    M _m;
    P1 _p1;
    P2 _p2;
    P3 _p3;
    P4 _p4;
    P5 _p5;
    P6 _p6;
};

#endif
