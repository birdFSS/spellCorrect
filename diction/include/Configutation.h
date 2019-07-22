#pragma once
#include <string>
#include <map>

namespace wd
{

class Configutation
{
public:
    Configutation(const std::string& fileName) : m_fileName(fileName) {}
    ~Configutation() {}
    std::map<std::string, std::string> &
    getConfigMap();
private:
    std::string m_fileName;
    std::map<std::string, std::string> m_configMap;
};







}//end of namespace wd

