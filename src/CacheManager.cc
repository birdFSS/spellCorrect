#include "../include/CacheManager.h"
#include "../include/Thread.h"

namespace wd
{

CacheManager* CacheManager::m_self = nullptr;


void CacheManager::initCache(size_t num, const std::string& fileName)
{
    Cache cache;
    cache.readFromFile(fileName);
    m_cacheFilePath = fileName;

#if CACHE_DEBUG
    printf("size = %ld\n", m_cacheVec.size());
#endif
    while(num-- > 0)
    {
        std::shared_ptr<MutexLock> pMtx(new MutexLock());
        m_cacheVec.push_back(cache);
        m_mutexs.push_back(pMtx);
    }

#if CACHE_DEBUG
    printf("size = %ld\n", m_cacheVec.size());
#endif
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
    size_t cId = current_thread::CacheIndex;
    getMostFrequentlyUsedData();

    for(size_t i=0;i<m_cacheVec.size(); ++i)
    {
        if(i == cId)
        {
            continue;
        }
        MutexLockGuard autolock(*m_mutexs[i]);
        m_cacheVec[i].update(m_cacheVec[cId]);
    }
    m_cacheVec[cId].writeToFile(m_cacheFilePath);

#if CACHE_DEBUG
    printf("write to file int Cache 0\n");
    m_cacheVec[cId].showList();
#endif
}

void CacheManager::getMostFrequentlyUsedData()   //将其他缓冲信息统一到一个list
{
    size_t id = current_thread::CacheIndex;
    size_t insertNum = CACHE_SIZE/ m_cacheVec.size();
    //cout << "insertNum = " << insertNum << endl
    //     << "CacheSize = " << CACHE_SIZE << endl
    //     << "Caches.size() = " << Caches.size() << endl;
    size_t j = 0;
    //循环遍历，每个Caches插入insertNum个数据,直到为空
    for(size_t i=0;i!=m_cacheVec.size();++i)
    {
        if(i == id)
        {
            continue;
        }
        j = 0;
        MutexLockGuard autolock(*m_mutexs[i]);
        for(auto iter = m_cacheVec[i].m_list.begin(); iter != m_cacheVec[i].m_list.end() && j != insertNum; ++iter,++j)
        {
                m_cacheVec[id].addElement(iter->m_key, iter->m_value);

#if CACHE_DEBUG
            printf("Cache %ld insert (%s-->%s)\n", id, iter->m_key.c_str(), iter->m_value.c_str());
#endif
        }
    }
}










}
