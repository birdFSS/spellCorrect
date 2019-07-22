#include "../include/DictProducer.h"
#include <iostream>
#include <fstream>
#include <sstream>

using std::ifstream;
using std::istringstream;
using std::cout;
using std::endl;

namespace wd
{

DictProducer::DictProducer(const string& dir) :
    m_dir(dir),
    m_splitTool(nullptr)
{
}

DictProducer::DictProducer(const string& dir, const string &ignorePath) :
    m_dir(dir),
    m_splitTool(nullptr)
{
    setIgnoreWords(ignorePath);
}

void DictProducer::setIgnoreWords(const string & path)
{
    ifstream ifs(path);
    string word;
    while(ifs >> word)
    {
        m_ignore.insert(word);
    }
}

void DictProducer::showDict() const
{
    auto it = m_dict.begin();
    while(it != m_dict.end())
    {
        cout << it->first << " " << it->second << endl;
        ++it;
    }
}


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
        ++it;
    }
}

void DictProducer::getFile() const
{
    cout << ">> path : " << m_dir << endl;
}

void DictProducer::showFilePath() const
{
    cout << ">> path : " << m_dir << endl;
}






















}
