#include "../include/DictProducer.h"
#include <iostream>
#include <fstream>
#include <sstream>

using std::ifstream;
using std::istringstream;

namespace wd
{

DictProducer::DictProducer(const string& dir) :
    m_dir(dir),
    m_splitTool(nullptr)
    {}

void DictProducer::DealOtherChar(string& str)
{
    for(auto& ch : str)
    {
        if(!isalpha(ch))
        {
            ch = ' ';
        }else if(isupper(ch)){
            ch = tolower(ch);
        }
    }
}

void DictProducer::buildDict()
{
    ifstream ifs(m_dir);
    string line;
    while(getline(ifs, line))
    {
        DealOtherChar(line);
        istringstream stream(line);
        string word;
        while(stream >> word)
        {
            pushDict(word);
        }
    }
}

void DictProducer::pushDict(const string& word)
{
    if(m_ignore.find(word) == m_ignore.end())
    {
        ++m_dict[word];
    }
}

void DictProducer::storeDict(const char* filePath)
{
    std::ofstream ofs(filePath);
    auto it = m_dict.begin();
    while(it != m_dict.end())
    {
        ofs << it->first << " " << it->second << std::endl;
    }
}


























}
