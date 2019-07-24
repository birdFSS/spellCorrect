#include "../include/Thread.h"


namespace wd 
{

void Thread::create()
{
    pthread_create(&m_pthid, nullptr, threadFunc, this);
    m_isRunning = true;
}


void Thread::join()
{
    if(m_isRunning)
    {
        pthread_join(m_pthid, nullptr);
    }
}

Thread::~Thread()
{
    if(m_isRunning)
        pthread_detach(m_pthid);
}

void * Thread::threadFunc(void * arg)
{
    Thread* pthread = static_cast<Thread*>(arg);
    if(pthread)
        pthread->m_call();
    return nullptr;
}

















}//wd



















