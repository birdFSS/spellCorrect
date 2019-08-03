#pragma once
#include "Cache.h"
#include "Mutexlock.h"
#include <vector>
#include <memory>
#include <iostream>

namespace wd
{

class CacheManager
{
public:
    static CacheManager* getInstance()
    {
        if(m_self == nullptr)
        {
            m_self = new CacheManager();
            atexit(destroy);
        }
        return m_self;
    }

    static void destroy()
    {
        if(m_self)
        {
            delete m_self;
        }
    }

    void initCache(size_t num, const std::string& fileName);

    Cache& getCache(size_t idx);

    std::vector<std::shared_ptr<MutexLock>>& getMutexs() { return m_mutexs; }

    void periodicUpdateCaches(); //定时更新所有缓存

    void getMostFrequentlyUsedData();   //将其他缓冲信息统一到一个list
private:
    CacheManager() {}

    ~CacheManager() {}

private:
    static CacheManager* m_self;
    std::vector<std::shared_ptr<MutexLock>>   m_mutexs;
    std::vector<Cache> m_cacheVec;
    std::string m_cacheFilePath;
};







}//end of namespace wd

