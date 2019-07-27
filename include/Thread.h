#pragma once
#include "Noncopyable.h"

#include <pthread.h>
#include <functional>
namespace wd
{

class Cache;

class Thread :
     Noncopyable
{
public:
    using ThreadCallBack = std::function<void()>;
    Thread(ThreadCallBack && cb) : 
        m_pthid(0),
        m_isRunning(false),
        m_pCache(nullptr),
        m_call(std::move(cb))
    {}

    Thread(ThreadCallBack && cb, Cache* pCache) : 
        m_pthid(0),
        m_isRunning(false),
        m_pCache(pCache),
        m_call(std::move(cb))
    {}

    void create();
    void join();
    ~Thread();


    static void * threadFunc(void * arg);

private:
    pthread_t m_pthid;
    bool m_isRunning;
    Cache* m_pCache;
    ThreadCallBack m_call;
};







}//end of namespace wd

