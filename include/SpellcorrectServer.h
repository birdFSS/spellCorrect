#pragma once
#include "MyConf.h"
#include "TcpServer.h"
#include "Threadpool.h"

#include <string>
namespace wd
{

class SpellcorrectServer
{
public:
    SpellcorrectServer(const std::string& fileName) :
        m_conf(*MyConf::getInstance(fileName)),
        m_tcpServer(m_conf.getConfig()["ip"],stoi( m_conf.getConfig()["port"])),
        m_threadpool(stoi(m_conf.getConfig()["threadNum"]),stoi(m_conf.getConfig()["queueSize"]))
    {
    }
    ~SpellcorrectServer() {}

private:
    MyConf& m_conf;    
    TcpServer m_tcpServer;
    Threadpool m_threadpool;
};







}//end of namespace wd

