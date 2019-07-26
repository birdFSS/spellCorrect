#include "Timer.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


namespace wd
{
Timer::Timer(int initSec, int intervalSec, TimeCallBack cb) :
    m_timerfd(createTimerfd()),
    m_isStarted(false),
    m_cb(cb)
{
    setTimer(initSec, intervalSec);    
}

Timer::~Timer()
{
    ::close(m_timerfd);
}

void Timer::start()
{
    m_isStarted = true;
    int ret = timerfd_settime(m_timerfd, 0, &m_ts, nullptr);
    if(-1 == ret)
    {
        perror("timerfd_settime");
    }
}

void Timer::stop()
{
    if(m_isStarted)
    {
        m_isStarted = false;
        setTimer(0,0);
    }
}

void Timer::handleRead()
{
    uint64_t num;
    int ret = ::read(m_timerfd, &num, sizeof(uint64_t));
    if(-1 == ret)
    {
        perror("ret");
    }
}

int Timer::createTimerfd()
{
    int fd = timerfd_create(CLOCK_REALTIME, 0);
    if(-1 == fd)
    {
        perror("timerfd_create");
    }
    return fd;

}

void Timer::setTimer(int initSec, int intervalSec)
{
    ::memset(&m_ts, 0, sizeof(struct itimerspec));
    m_ts.it_value.tv_sec = initSec;
    m_ts.it_value.tv_nsec = 0;
    m_ts.it_interval.tv_sec = intervalSec;
    m_ts.it_interval.tv_nsec = 0;
}











}
