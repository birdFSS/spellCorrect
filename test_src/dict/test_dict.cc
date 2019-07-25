#include "../include/MyDict.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;
using namespace wd;

void test0()
{
    //测试词典的读入
    MyDict* dict = MyDict::getInstance();
    dict->init("../dictionary/data/en_dict.uft8", "../dictionary/data/cn_dict.utf8");
    dict->showDictInTestFile();
}

void test1()
{
    //测试词典加上索引
    MyDict* dict = MyDict::getInstance();
    dict->init("../dictionary/data/en_dict.uft8", "../dictionary/data/cn_dict.utf8",
                "../dictionary/data/index.utf8");
    dict->showDictInTestFile(); 
    dict->showTableInTestFile();
}

void test2()
{
    //测试通过索引输出相关词
    MyDict* dict = MyDict::getInstance();
    dict->init("../dictionary/data/en_dict.uft8", "../dictionary/data/cn_dict.utf8",
                "../dictionary/data/index.utf8");
    auto& dict_vec = dict->getDict();
    auto& index = dict->getIndexTable();
    string str("土");
    for(auto& i : index[str])
    {
        cout << dict_vec[i].first << " --> " << dict_vec[i].second << endl;
    }
}

int main()
{
    test2();
    return 0;
}

