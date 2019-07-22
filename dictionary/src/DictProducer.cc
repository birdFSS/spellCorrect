#include "../include/DictProducer.h"
#include "../include/cppjieba/Jieba.hpp"
#include <limits.h>
#include <stdlib.h>
#include <dirent.h>
#include<sys/types.h>
#include<unistd.h>
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
    getDirAbosolutePath();
    getFileAbosolutePath();
    //cout << m_dir << endl;
    //遍历目录，将文件的绝对路径都加进来
}

DictProducer::DictProducer(const string& dir, const string &ignorePath) :
    m_dir(dir),
    m_splitTool(nullptr)
{
    setIgnoreWords(ignorePath);
}

void DictProducer::setIgnoreWords(const string & path)
{
    if(path.size() == 0)
    {
        cout << "ignore path is empty" << endl;
        return ;
    }
    ifstream ifs(path);
    string word;
    while(getline(ifs,word))
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
#if 0
void DictProducer::buildCnDict()
{
    cppjieba::Jieba jieba
}
#endif

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

void DictProducer::getDirAbosolutePath()
{
    char buf[1024] = {0};
    if(realpath(m_dir.c_str(), buf))
    {
        m_dir = buf;
    }else{
        perror("realpath");
    }
}

void DictProducer::getFileAbosolutePath()   //获取文件的绝对路径
{
    DIR* dir = opendir(m_dir.c_str());
    if(nullptr == dir)
    {
        perror("opendir");
        return ;
    }
    struct dirent *d;
    string filePath;
    while((d = readdir(dir)) != NULL)
    {
        if(d->d_type & DT_REG)
        {
            filePath = m_dir + "/" + d->d_name;
            m_filePath.push_back(filePath);
        }
    }

    int ret = closedir(dir);
    if(-1 == ret)
    {
        perror("closedir");
        return;
    }
}
void DictProducer::showFilePath() const
{
    cout << ">> dir path : " << m_dir << endl;
    for(auto i : m_filePath)
    {
        cout << i << endl;
    }
}

void DictProducer::showIgnoreWords() const
{
    cout << "ignore word " << endl;
    for(auto i : m_ignore)
    {
        cout << i << endl;
    }
}




















}
