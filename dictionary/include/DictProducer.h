#pragma once

#include <string>
#include <map>
#include <set>
#include <vector>
using std::string;
using std::map;
using std::set;
using std::vector;

namespace wd
{

class SplitTool;

class DictProducer
{
public:
    DictProducer(const string& dir);        //英文
    DictProducer(const string& dir, const string &ignorePath);    //英文
    DictProducer(const string& dir, SplitTool* splitTool); //中文
    
    void setIgnoreWords(const string & path);
    void buildDict();
    void buildCnDict();

    void storeDict(const char* filePath);

    void showFilePath() const; //测试接口
    void showDict() const; //测试接口
    void getFile() const;  //获取文件的绝对路径
    void pushDict(const string& word);  //存储某个单词

private:
    void DealOtherChar(string& str);    //处理标点和将大写字母变为小写
private:
    string m_dir;       //语料库文件存放路径
    vector<string> m_filePath;  //语料库文件的绝对路劲集合
    map<string, int> m_dict;    //单词 词频
    set<string> m_ignore;       //忽略一些简单的单词
    SplitTool * m_splitTool;
};







}//end of namespace wd

