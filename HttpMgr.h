#ifndef _HTTP_MGR_H_
#define _HTTP_MGR_H_

#include "Singleton.h"
#include "Condition.h"

#include <curl/curl.h>

#include <string>
#include <vector>
#include <list>
using namespace std;

/**
 * @class HttpMgr
 */
class HttpMgr : public Singleton<HttpMgr>
{
    friend class Singleton<HttpMgr>;

public:
    /**
     * @class QStr
     *
     * represent QueryString for http-get
     */
    class QStr
    {
        friend class HttpMgr;

    public:
        QStr(uint32 hint_n = 3)
        {
            _qs_kv.reserve(hint_n * 2);
        }

        ~QStr() {}

    public:
        QStr &add(const char *k, const char *v);
        QStr &add(const char *k, int32 v);
        QStr &add(const char *k, uint32 v);

        inline bool empty() const
        {
            return _qs_kv.empty();
        }

        inline void reset()
        {
            _qs_kv.clear();
        }

    private:
        /// dump non-escaped querystring
        string dump();

        /// dump escaped querystring
        bool escape(CURL *h, string &ret);

    private:
        vector<string> _qs_kv;
    };

protected:
    HttpMgr()
        : _curl_ginit(false)
        , _pool_cond(_pool_lock)
    {}

public:
    ~HttpMgr()
    {
        this->close();
    }

public:
    bool open(int thread_cnt, const char *ca_bundle = 0);
    void close();

    // these 2 methods are thread safe
    bool get(const char *addr, QStr &qstr, string &ret);
    bool post(const char *addr, const char *data, string &ret);

private:
    /// curl write callback
    static size_t on_curl_write(char *ptr, size_t size, size_t nmemb, void *ud);

    /// curl pool methods
    CURL *get_curl(bool poll = false);
    void free_curl(CURL *h);

private:
    bool _curl_ginit;

    /// curl handle pool
    typedef list<CURL *> CURLList;
    CURLList _curl_pool;

    Thread_Mutex _pool_lock;
    Condition _pool_cond;
};

#define sHttpMgr (*HttpMgr::instance())

#endif
