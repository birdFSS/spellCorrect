#pragma once
#include "InetAddress.h"
namespace wd
{

class Client
{
public:
    Client(const string& ip, unsigned short port) :
        m_fd(0),
        m_addr(ip, port)
    {}
    ~Client() {}

    void run();
    int getFd() const
    { return m_fd; }

private:
    void connectToServer();
private:
    int m_fd;
    InetAddress m_addr;
};







}//end of namespace wd

