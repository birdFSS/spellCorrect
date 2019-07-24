#include "TaskQueue.h"
#include <iostream>

using std::cout;
using std::endl;

namespace wd
{

TaskQueue::TaskQueue(size_t queSize) :
    m_queSize(queSize),
    m_isOpen(true),
    m_mutex(),
    m_notFull(m_mutex),
    m_notEmpty(m_mutex)
{

}

void TaskQueue::wakeup()
{
    m_isOpen = false;
    m_notFull.notifyAll();
    m_notEmpty.notifyAll();
}

bool TaskQueue::empty()  const 
{
    return m_que.size() == 0;
}

bool TaskQueue::full() const 
{
    return m_que.size() == m_queSize;
}

void TaskQueue::push(valueType number)
{
    MutexLockGuard autolock(m_mutex);
    while(m_isOpen && full())
    {
        m_notFull.wait();
    }

    m_que.push(number);
    m_notEmpty.notify();
}

TaskQueue::valueType TaskQueue::pop()
{
    MutexLockGuard autolock(m_mutex);
    while(m_isOpen && empty())
    {
        m_notEmpty.wait();
    }
    if(m_isOpen){
        valueType number = m_que.front();
        m_que.pop();

        m_notFull.notify();
        return number;
    }else{
        pthread_exit(NULL);
    }
}












}































