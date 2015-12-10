#include "HttpMgr.h"

#include "Guard.h"
#include <stdio.h>
// ------------------------------------- QStr -------------------------------------

HttpMgr::QStr &HttpMgr::QStr::add(const char *k, const char *v)
{
    _qs_kv.push_back(k);
    _qs_kv.push_back(v);
    return *this;
}

HttpMgr::QStr &HttpMgr::QStr::add(const char *k, int32 v)
{
    char buf[16];
    sprintf(buf, "%d", v);

    _qs_kv.push_back(k);
    _qs_kv.push_back(buf);
    return *this;
}

HttpMgr::QStr &HttpMgr::QStr::add(const char *k, uint32 v)
{
    char buf[16];
    sprintf(buf, "%u", v);

    _qs_kv.push_back(k);
    _qs_kv.push_back(buf);
    return *this;
}

string HttpMgr::QStr::dump()
{
    char qs[4096];
    qs[sizeof(qs) - 1] = 0;

    int idx = 0;
    int n;

    for (uint32 i = 0; i < _qs_kv.size(); i += 2)
    {
        n = snprintf(qs + idx, sizeof(qs) - idx - 1, "&%s=%s",
                     _qs_kv[i].c_str(), _qs_kv[i + 1].c_str());
        if (n < 0) break;

        idx += n;
    }

    // return
    return idx > 0 ? &qs[1] : "";
}

bool HttpMgr::QStr::escape(CURL *h, string &ret)
{
    char qs[4096];
    qs[sizeof(qs) - 1] = 0;

    char *enc;
    int idx = 0;
    int n;

    for (uint32 i = 0; i < _qs_kv.size(); i += 2)
    {
        enc = curl_easy_escape(h, _qs_kv[i + 1].c_str(), (int)_qs_kv[i + 1].length());
        if (!enc) return false;

        n = snprintf(qs + idx, sizeof(qs) - idx - 1, "&%s=%s", _qs_kv[i].c_str(), enc);
        curl_free(enc);

        if (n < 0) return false;

        idx += n;
    }

    // set return value
    if (idx > 0)
        ret = &qs[1];
    else
        ret.clear();

    return true;
}

// ------------------------------------ HttpMgr -----------------------------------

bool HttpMgr::open(int thread_cnt, const char *ca_bundle)
{
    if (curl_global_init(CURL_GLOBAL_ALL) != CURLE_OK) return false;
    _curl_ginit = true;

    CURL *h;
    for (int i = 0; i < thread_cnt; i++)
    {
        h = curl_easy_init();
        if (!h)
        {
            this->close();
            return false;
        }

        // prevent the default resolver of curl from emitting SIGABRT for timeout
        curl_easy_setopt(h, CURLOPT_NOSIGNAL, 1);

        curl_easy_setopt(h, CURLOPT_FOLLOWLOCATION, 1);
        curl_easy_setopt(h, CURLOPT_WRITEFUNCTION, &HttpMgr::on_curl_write);

        // set ca-bundle for ssl
        if (ca_bundle)
        {
            curl_easy_setopt(h, CURLOPT_SSL_VERIFYPEER, 1);
            curl_easy_setopt(h, CURLOPT_CAINFO, ca_bundle);
        }
        else
        {
            curl_easy_setopt(h, CURLOPT_SSL_VERIFYPEER, 0);
        }

        _curl_pool.push_back(h);
    }

    return true;
}

void HttpMgr::close()
{
    for (CURLList::iterator it = _curl_pool.begin(); it != _curl_pool.end(); ++it)
    {
        curl_easy_cleanup(*it);
    }
    _curl_pool.clear();

    if (_curl_ginit)
    {
        curl_global_cleanup();
        _curl_ginit = false;
    }
}

bool HttpMgr::get(const char *addr, QStr &qstr, string &ret)
{
    printf("executing http-get:\n\t\t%s%s%s",
            addr,
            qstr.empty() ? "" : "?",
            qstr.empty() ? "" : qstr.dump().c_str());

    // get curl
    CURL *h = this->get_curl();

    bool r = false;
    do
    {
        // set http-get
        curl_easy_setopt(h, CURLOPT_HTTPGET, 1);

        // set url
        if (qstr.empty())
        {
            curl_easy_setopt(h, CURLOPT_URL, addr);
        }
        else
        {
            // get querystring
            string qs;
            if (!qstr.escape(h, qs)) break;

            char url[1024];
            url[sizeof(url) - 1] = 0;
            snprintf(url, sizeof(url) - 1, "%s?%s", addr, qs.c_str());
            curl_easy_setopt(h, CURLOPT_URL, url);
        }

        // set ret data
        ret.clear();
        curl_easy_setopt(h, CURLOPT_WRITEDATA, &ret);

        // perform
        CURLcode res = curl_easy_perform(h);
        if (res != CURLE_OK) break;

        // check status code
        uint32 status;
        res = curl_easy_getinfo(h, CURLINFO_RESPONSE_CODE, &status);
        if (res != CURLE_OK || status != 200) break;

        // succeed
        r = true;
    }
    while (0);

    // put back curl
    this->free_curl(h);

    return r;
}

bool HttpMgr::post(const char *addr, const char *data, string &ret)
{
    printf("executing http-post:\n\t\t%s\n\t\t%s", addr, data);

    // get curl
    CURL *h = this->get_curl();

    bool r = false;
    do
    {
        // set url
        curl_easy_setopt(h, CURLOPT_URL, addr);

        // set post data
        curl_easy_setopt(h, CURLOPT_POSTFIELDS, data);

        // set ret data
        ret.clear();
        curl_easy_setopt(h, CURLOPT_WRITEDATA, &ret);

        // perform
        CURLcode res = curl_easy_perform(h);
        if (res != CURLE_OK) break;

        // check status code
        uint32 status;
        res = curl_easy_getinfo(h, CURLINFO_RESPONSE_CODE, &status);
        if (res != CURLE_OK || status != 200) break;

        // succeed
        r = true;
    }
    while (0);

    // put back curl
    this->free_curl(h);

    return r;
}

size_t HttpMgr::on_curl_write(char *ptr, size_t size, size_t nmemb, void *ud)
{
    string *data = (string *)ud;

    data->append(ptr, size * nmemb);
    return size * nmemb;
}

CURL *HttpMgr::get_curl(bool poll)
{
    CURL *h = 0;

    Guard<Thread_Mutex> g(_pool_lock);

    if (poll && _curl_pool.empty()) return 0;

    while (_curl_pool.empty())
    {
        _pool_cond.wait();
    }

    h = _curl_pool.front();
    _curl_pool.pop_front();

    return h;
}

void HttpMgr::free_curl(CURL *h)
{
    Guard<Thread_Mutex> g(_pool_lock);

    _curl_pool.push_back(h);
    _pool_cond.signal();
}
