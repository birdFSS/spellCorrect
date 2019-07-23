#pragma once
#include <vector>
#include <map>

namespace wd
{

class MyDict
{
public:
    static MyDict* getInstance() 
    {
        if(m_self == nullptr)
        {
            m_self = new MyDict();
        }
        return m_self;
    }
    static void destroy()
    {
        if(m_self != nullptr)
        {
            delete m_self;
            m_self = nullptr;
        }
    }
private:
    MyDict() {}
    ~MyDict() {}

private:
    static MyDict * m_self;
    std::vector<std::pair<std::string,int>> m_dict;
    std::map<std::string,int> m_index_table;
};







}//end of namespace wd

