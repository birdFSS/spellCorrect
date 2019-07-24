#pragma once
#include "Noncopyable.h"

#include <pthread.h>
#include <functional>
namespace wd
{

class Thread :
     Noncopyable
{
public:
    using ThreadCallBack = std::function<void()>;
    Thread(ThreadCallBack && cb) : 
        m_pthid(0),
        m_isRunning(false),
        m_call(std::move(cb))
    {}

    void create();
    void join();
    ~Thread();


    static void * threadFunc(void * arg);

private:
    pthread_t m_pthid;
    bool m_isRunning;
    ThreadCallBack m_call;
};







}//end of namespace wd

