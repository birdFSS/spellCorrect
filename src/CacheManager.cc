#include "../include/CacheManager.h"


namespace wd
{

CacheManager* CacheManager::m_self = nullptr;


void CacheManager::initCache(size_t num, const std::string& fileName)
{
    Cache cache;
    cache.readFromFile(fileName);
    m_cacheFilePath = fileName;
    while(num-- > 0)
    {
        m_cacheVec.push_back(cache);
    }
}

Cache& CacheManager::getCache(size_t idx)
{   
    if(idx < m_cacheVec.size())
        return m_cacheVec[idx]; 
    else{
        return m_cacheVec[0];
    }
}

void CacheManager::periodicUpdateCaches() //定时更新所有缓存
{
    for(size_t i=1;i<m_cacheVec.size(); ++i)
    {
        m_cacheVec[0].update(m_cacheVec[i]);
    }


    for(size_t i=1;i<m_cacheVec.size(); ++i)
    {
        m_cacheVec[i].update(m_cacheVec[0]);
    }
    m_cacheVec[0].writeToFile(m_cacheFilePath);
}











}
