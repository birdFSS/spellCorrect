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
    m_hashMap(cache.getHashMap().begin(), cache.getHashMap().end())
{

}

Cache::~Cache()
{

}
//后面加上lru算法
void Cache::addElement(const std::string& key, const std::string &value)
{
    m_hashMap.insert(make_pair(key, value));
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


void Cache::writeToFile(const std::string& fileName)
{
    ofstream ofs(fileName);
    for(auto it = m_hashMap.begin(); it != m_hashMap.end(); ++it)
    {
        ofs << it->first << " " << it->second << endl;
    }
}

void Cache::update(const Cache& rhs)
{
    for(auto it = rhs.getHashMap().cbegin(); it != m_hashMap.cend(); ++it)
    {
        addElement(it->first, it->second);
    }
}





}
