#pragma once
#include <unordered_map>

namespace wd
{

class Cache
{
public:
    Cache();
    Cache(const Cache& cache);
    ~Cache();
    void addElement(const std::string& key, const std::string &value);
    void readFromFile(const std::string& fileName);
    void writeToFile(const std::string& fileName);
    void update(const Cache& rhs);
    const std::unordered_map<std::string, std::string>&
    getHashMap() const 
    { return m_hashMap; }
private:
    std::unordered_map<std::string, std::string> m_hashMap;
};







}//end of namespace wd

