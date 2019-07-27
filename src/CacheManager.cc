#include "../include/CacheManager.h"


namespace wd
{
CacheManager* CacheManager::m_self = nullptr;
std::vector<Cache> CacheManager::m_cacheList;
std::string CacheManager::m_cacheFilePath;




}//wd
