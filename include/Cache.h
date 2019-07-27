#pragma once
#include <unordered_map>
#include <list>
#define CACHE_SIZE 5

namespace wd
{


class Cache
{
    struct CacheNode
    {
        CacheNode(const std::string& key,const std::string value) :
            m_key(key),
            m_value(value)
        {}
        std::string m_key;
        std::string m_value;
    };
public:
    Cache();
    Cache(const Cache& cache);
    ~Cache();
    void addElement(const std::string& key, const std::string &value);
    void readFromFile(const std::string& fileName);
    void writeToFile(const std::string& fileName);
    void update(const Cache& rhs);

private:
    std::list<CacheNode> m_list;
    std::unordered_map<std::string, std::list<CacheNode>::iterator> m_hashMap;
};







}//end of namespace wd

