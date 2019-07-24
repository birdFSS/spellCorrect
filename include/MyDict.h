#pragma once
#include <vector>
#include <set>
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
            atexit(destroy);
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

    std::vector<std::pair<std::string,int>>&  getDict()
    {
        return m_dict;
    }

    std::map<std::string,std::set<int>>& getIndexTable()
    { return m_index_table; }

    void init(const std::string& dictEnPath, const std::string& dictCnPath);
    void init(const std::string& dictEnPath, const std::string& dictCnPath,const std::string& IndexTablePath);

    void showTableInTestFile(const std::string& path = "../test/table_test.txt");
    void showDictInTestFile(const std::string& path = "../test/map_test.txt");

    void setIndexTable(const std::string& IndexTablePath);
private:
    MyDict() {}
    ~MyDict() {}


private:
    static MyDict * m_self;
    std::vector<std::pair<std::string,int>> m_dict;
    std::map<std::string,std::set<int>> m_index_table;
};







}//end of namespace wd

