#include "../include/MyTask.h"
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

void test0()
{
    //查询最短编辑距离的词
    wd::MyTask task("海",0);
    task.excute();
    task.showQueue();

    wd::MyTask task1("ful", 0);
    task1.excute();
    task1.showQueue();
}

int main()
{
    test0();
    return 0;
}

