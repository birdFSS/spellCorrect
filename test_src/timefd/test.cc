#include "Timer.h"
#include <sys/epoll.h>
#include <unistd.h>
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
    wd::Timer timer(3,1,[](){cout << "timer naonao qieke nao" << endl;});
    timer.start();
    //timer.stop();
    while(1)
    {
        timer.handleRead();
        cout << "naonaoqiekenao" << endl;
    }
}

int main()
{
    test0();
    return 0;
}

