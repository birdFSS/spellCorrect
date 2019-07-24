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
}

void test1()
{
    MyDict* dict = MyDict::getInstance();
    dict->init("../dictionary/data/en_dict.uft8", "../dictionary/data/cn_dict.utf8",
                "../dictionary/data/index.utf8");
}

int main()
{
    test1();
    return 0;
}

