#include "../include/Cache.h"
#include <fstream>
#include <iostream>
using std::cout;
using std::endl;
using std::string;
using std::ofstream;
using std::ifstream;

namespace wd
{

Cache::Cache()
{

}

Cache::Cache(const Cache& cache) :
    m_list(cache.m_list),
    m_hashMap(cache.m_hashMap)
{

}

Cache::~Cache()
{
    //回收空间
    auto iter = m_hashMap.begin();
    while(iter != m_hashMap.end())
    {
        delete &*iter->second;
        ++iter;
    }
}

//LRU算法
void Cache::addElement(const std::string& key, const std::string &value)
{
    //查找关键字是否在hash表中
    auto iter = m_hashMap.find(key);
    if(iter != m_hashMap.end())
    {
        //在hash表中，将其从链表中取出来，再插入链表头
        m_list.erase(iter->second);
        m_list.push_front(*iter->second);
    }else{
        //不再hash表中，新建一个节点，将节点放在链表头，如果Cache满了，
        //则将链表尾结点删除
        CacheNode* pNode = new CacheNode(key, value);
        m_list.push_front(*pNode);
        m_hashMap.insert(make_pair(key, m_list.begin()));
        if(m_list.size() > CACHE_SIZE)
        {
            string key = m_list.back().m_key;
            m_list.pop_back();
            auto iter = m_hashMap.find(key);
            delete &*iter->second;
            m_hashMap.erase(iter);
        }

    }
}

void Cache::readFromFile(const std::string& fileName)
{
    ifstream ifs(fileName);
    string key, value;
    while(ifs >> key >> value)
    {
        addElement(key, value);
    }
}

//反向写入文件，这样读入的时候顺序是对的
//即读出时的队头的是与写入前一样的
void Cache::writeToFile(const std::string& fileName)
{
    ofstream ofs(fileName);
    for(auto it = m_list.rbegin(); it != m_list.rend(); ++it)
    {
        ofs << it->m_key << " " << it->m_value << endl;
    }
}


//current 
void Cache::update(const Cache& rhs)
{
    for(auto it = rhs.getHashMap().cbegin(); it != m_hashMap.cend(); ++it)
    {
        addElement(it->first, it->second);
    }
}





}
