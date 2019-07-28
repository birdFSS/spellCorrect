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
        //在hash表中，将其从链表中取出来，再插入链表头,更新哈希表
        m_list.erase(iter->second);
        m_list.push_front(*iter->second);
        iter->second = m_list.begin();
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
    //如果Cache没满，那么rhs中的缓存就加入了this 中了
    //如果满了，那么rhs中的缓存就代替this中缓存
    for(auto it = rhs.m_list.begin(); it != rhs.m_list.end(); ++it)
    {
        addElement(it->m_key, it->m_value);
    }
}


void Cache::getMostFrequentlyUsedData(std::vector<Cache>& Caches)   //将其他缓冲信息统一到一个list
{
    int size = Caches.size();
    int needData = CACHE_SIZE;
    CacheNode* pCacheNode;
    for(int i=1;needData-- != 0;++i)
    {
        if(i == size)
        {
            i = 1;
        }

        if(Caches[i].m_list.size() != 0)
        {
            pCacheNode = &Caches[i].m_list.front(); //链表头是最新的
            //原来所在的缓冲区先除去该结点
            Caches[i].m_list.pop_front();
            Caches[i].m_hashMap.erase(pCacheNode->m_key);
        }else{
            continue;
        }

        //将结点移到Cache 0 的链表头
        //先判断该结点是否存在
        auto iter_key = Caches[0].m_hashMap.find(pCacheNode->m_key);
        if(iter_key == Caches[0].m_hashMap.end())
        {
            Caches[0].m_list.push_front(*pCacheNode);
            Caches[0].m_hashMap.insert(make_pair(pCacheNode->m_key, Caches[0].m_list.begin()));
        }else{
            //先移除链表中的
            Caches[0].m_list.erase(iter_key->second);
            delete &*iter_key->second;
            Caches[0].m_hashMap.erase(iter_key);
            
            //在添加新的结点
            Caches[0].m_list.push_front(*pCacheNode);
            Caches[0].m_hashMap.insert(make_pair(pCacheNode->m_key, Caches[0].m_list.begin()));
        }
        //这里可以直接判断Cache[0]是否超过大小而去删除结点，但是考虑到后面可能还会加入，是不是统一删除会好一点
        //可能潜在的条件 重复的CacheNode比较多，所以可以统一进行删除，减少开销
    }



    //对于Cache 0 多出的结点统一进行删除
    while(Caches[0].m_list.size() > CACHE_SIZE)
    {
        CacheNode* pNode = &Caches[0].m_list.back();
        Caches[0].m_list.pop_back();
        Caches[0].m_hashMap.erase(pNode->m_key);
        delete pNode;
    }
}






















}
