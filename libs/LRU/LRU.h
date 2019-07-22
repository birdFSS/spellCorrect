#include <list>
#include <unordered_map>
using std::list;
using std::pair;
using std::unordered_map;
using std::make_pair;
class LRUCache {
public:
    LRUCache(int capacity) :
        m_capacity(capacity)
    {


    }

    int get(int key) {
        auto iter = m_umap.find(key);
        if(iter != m_umap.end())
        {
            int temp = iter->second->second;
            m_list.erase(iter->second);
            m_list.push_back(make_pair(key, temp));
            m_umap[key] = --m_list.end();
            return m_umap[key]->second;

        }else{
            return -1;

        }

    }

    void put(int key, int value) {
        auto iter = m_umap.find(key);
        if( iter != m_umap.end() )
        {
            m_list.erase(iter->second);

        }
        m_list.push_back(make_pair(key, value));
        m_umap[key] = --m_list.end();

        if(m_list.size() > m_capacity)
        {
            int key = m_list.front().first;
            m_umap.erase(key);
            m_list.pop_front();

        }

    }

private:
    std::unordered_map<int, list<pair<int,int>>::iterator> m_umap;
    list<pair<int,int>> m_list;
    size_t m_capacity;
};
