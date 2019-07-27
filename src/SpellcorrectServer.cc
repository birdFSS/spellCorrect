#include "../include/SpellcorrectServer.h"
#include "../include/CacheManager.h"
#include "../include/MyTask.h"
#include "../include/CacheManager.h"
#include <string>
#include <iostream>
#include <string>
#include <functional>

using std::cout;
using std::endl;
namespace wd
{

void SpellcorrectServer::onConnection(const wd::TcpConnectionPtr & conn)
{
    cout << conn->toString() << " has connected!" << endl;
}

void SpellcorrectServer::onClose(const wd::TcpConnectionPtr & conn)
{
    cout << ">> " << conn->toString() << " has closed!" << endl;
}

void SpellcorrectServer::onMessage(const wd::TcpConnectionPtr & conn)
{
    //该回调函数实际不宜过长 2ms
    cout << "onMessage..." << endl;
    string msg = conn->receive();       
    cout << ">> receive msg from client : " << msg << endl;
    
    wd::MyTask task(msg,conn->getPeerFd(),conn);
    m_threadpool.addTask(
        std::bind(&wd::MyTask::excute, task, CacheManager::getInstance()->getCache(m_cacheId))
    );
    m_cacheId = (m_cacheId + 1) % m_threadpool.getThreadNum();
}

void SpellcorrectServer::start()
{
    CacheManager* pCache = CacheManager::getInstance();
    pCache->initCache(stoi(m_conf.getConfig().at("threadNum")), m_conf.getConfig().at("cacheFilePath"));
    auto& config = m_conf.getConfig();
    
    auto pCacheMana = CacheManager::getInstance();
    pCacheMana->initCache(stoi(config.at("threadNum")), config.at("cacheFilePath"));

    m_timer = std::make_shared<TimerThread>(
        TimerThread(stoi(config.at("initTime")),stoi(config.at("intervalTime")),
                    std::bind(&CacheManager::periodicUpdateCaches,pCacheMana))
    );

    m_timer->start();

    m_threadpool.start();

    using namespace std::placeholders;
    m_tcpServer.setConnectionCallBack(std::bind(&SpellcorrectServer::onConnection, this, _1));
    m_tcpServer.setMessageCallBack(std::bind(&SpellcorrectServer::onMessage, this, _1));
    m_tcpServer.setCloseCallBack(std::bind(&SpellcorrectServer::onClose, this, _1));
    m_tcpServer.start();

}

















}//wd

