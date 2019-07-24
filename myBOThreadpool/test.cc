#include "Thread.h"
#include "Threadpool.h"
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <memory>

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;
using std::unique_ptr;
using wd::Threadpool;
class MyTask
{
public:
    void process()
    {
        ::srand(::clock());
        int number = ::rand() % 100;
        cout << "sub Thread " << pthread_self()
            << " : number = "<< number << endl;
        ::sleep(1);
    }
    ~MyTask() { cout << "   ~MyTask() " << endl; }
};
int main()
{
    Threadpool threadpool;
    threadpool.start();
    MyTask task;
    int cnt = 20;
    while(cnt --){
        threadpool.addTask(std::bind(&MyTask::process, &task));
        cout << " main thread " << pthread_self()
            << " : cnt = " << cnt << endl;
    }

    threadpool.stop();
    return 0;
}

