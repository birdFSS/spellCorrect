#pragma once
#include <unordered_map>
#include <list>
#include <iostream>
#include <vector>
#define CACHE_SIZE 11


#define CACHE_DEBUG 0

namespace wd
{


class Cache
{
    friend class MyTask;
    friend class CacheManager;
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
    size_t getListSize() { return m_list.size(); }
    

    void showList() const       //test
    {
        std::cout << "--------list-----------------------" << std::endl;
        for(auto& node : m_list)
        {
            std::cout << node.m_key << "-->" << node.m_value << std::endl;
        }
    }

private:
    std::list<CacheNode> m_list;
    std::unordered_map<std::string, std::list<CacheNode>::iterator> m_hashMap;
};







}//end of namespace wd

