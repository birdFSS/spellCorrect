#include "../include/Configuration.h"
#include "../include/DictProducer.h"
#include "../include/CppJieba.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;

void test0()
{
    //测试读取配置文件信息
    wd::Configuration conf("../conf/config.txt");
    auto confMap = conf.getConfigMap();
    for(auto i : confMap)
    {
        cout << i.first << "--->" << i.second << endl;
    }
}

void test1()
{
    //测试读取语料库文件的绝对位置
    wd::Configuration conf("../conf/config.txt");
    auto confMap = conf.getConfigMap();

    wd::DictProducer dict(confMap["dir"]);
    wd::DictProducer CNdict(confMap["cndir"]);

    dict.showFilePath();
    CNdict.showFilePath();
}

void test2()
{
    wd::Configuration conf("../conf/config.txt");
    auto confMap = conf.getConfigMap();

    wd::DictProducer dict(confMap["dir"]);
    wd::DictProducer CNdict(confMap["cndir"]);

    dict.setIgnoreWords(confMap["en_ignore"]);
    CNdict.setIgnoreWords(confMap["cn_ignore"]);
    
    //dict.showIgnoreWords();
    CNdict.showIgnoreWords();
}

void test3()
{
    //测试中文分词，构建中文词典
    std::shared_ptr<wd::SplitTool> pst(new wd::CppJieba());
    wd::Configuration conf("../conf/config.txt");
    auto confMap = conf.getConfigMap();

    wd::DictProducer CNdict(confMap["cndir"], pst);
    CNdict.setIgnoreWords(confMap["cn_ignore"]);
    CNdict.buildCNDict();
    //CNdict.showIgnoreWords(); //展示忽略的字词
    CNdict.storeDict("../data/dict_cn.txt");
}

int main()
{
    test3();
    //dict.buildDict();
    //dict.showDict();
    //dict.storeDict("../data/dict_test.txt");
    return 0;
}



