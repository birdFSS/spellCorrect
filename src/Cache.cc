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
    m_list(cache.m_list)
{
    for(auto iter = m_list.begin(); iter != m_list.end(); ++iter)
    {
        m_hashMap.insert(make_pair(iter->m_key, iter));
    }
}

Cache::~Cache()
{
}

//LRU算法
void Cache::addElement(const std::string& key, const std::string &value)
{
    //查找关键字是否在hash表中
    auto iter = m_hashMap.find(key);

    //在hash表中，将其从链表中取出来，再插入链表头,更新哈希表
    if(iter != m_hashMap.end())
    {
        m_list.erase(iter->second);
        m_list.push_front(CacheNode(key,value));
        iter->second = m_list.begin();
    }else{
        //不再hash表中，新建一个节点，将节点放在链表头，如果Cache满了，
        //则将链表尾结点删除
        m_list.push_front(CacheNode(key,value));
        m_hashMap.insert(make_pair(key, m_list.begin()));
        if(m_list.size() > CACHE_SIZE)
        {
            string oldKey = m_list.back().m_key;
            m_list.pop_back();
            auto iter_oldKey = m_hashMap.find(oldKey);
            m_hashMap.erase(iter_oldKey);
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
    //如果Cache没满，那么rhs中的缓存就加入了this 中了
    //如果满了，那么rhs中的缓存就代替this中缓存
    for(auto it = rhs.m_list.begin(); it != rhs.m_list.end(); ++it)
    {
        addElement(it->m_key, it->m_value);
    }
}

#if 0
void Cache::getMostFrequentlyUsedData(std::vector<Cache>& Caches)   //将其他缓冲信息统一到一个list
{
    int num = CACHE_SIZE;
    bool CacheEmpty[CACHE_SIZE] = {0};
    for(int i=1;num != 0;++i)
    {
        if(Caches[i].m_list.size() != 0)
        {
            
            --num;
        }else{
            CacheEmpty[i] = true;
        }
    }

}

#endif





















}
