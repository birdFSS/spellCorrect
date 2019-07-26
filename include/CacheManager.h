#pragma once
#include "Cache.h"
#include <vector>

namespace wd
{

class CacheManager
{
public:
    static void initCache(size_t num, const std::string& fileName)
    {
        Cache cache;
        cache.readFromFile(fileName);
        m_cacheFilePath = fileName;
        while(num-- > 0)
        {
            m_cacheList.push_back(cache);
        }
    }

    static Cache& getCache(size_t idx)
    {   
        if(idx < m_cacheList.size())
            return m_cacheList[idx]; 
        else{
            return m_cacheList[0];
        }
    }

    static void periodicUpdateCaches() //定时更新所有缓存
    {
        for(size_t i=1;i<m_cacheList.size(); ++i)
        {
            m_cacheList[0].update(m_cacheList[i]);
        }

        for(size_t i=1;i<m_cacheList.size(); ++i)
        {
            m_cacheList[i].update(m_cacheList[i]);
        }
        m_cacheList[0].writeToFile(m_cacheFilePath);
    }

    CacheManager() {}

    ~CacheManager() {}

private:
    static std::vector<Cache> m_cacheList;
    static std::string m_cacheFilePath;
};







}//end of namespace wd

