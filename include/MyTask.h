#pragma once

#include <vector>
#include <string>
#include <set>
#include <queue>

namespace wd
{

class Cache;
struct MyResult
{
    MyResult(const std::string& word, int freq, int dist) :
        m_word(word),
        m_freq(freq),
        m_dist(dist)
    {}
    std::string m_word; //候选词
    int m_freq; //词频
    int m_dist; //最小距离
};

class MyCompare
{
public:
    bool operator()(const MyResult& lhs, const MyResult& rhs)
    {
        return lhs.m_dist > rhs.m_dist;
    }
};


class MyTask
{
public:
    MyTask(const std::string& word, int peerfd):
        m_queryWord(word),
        m_peerfd(peerfd)
    {}
    ~MyTask() {}
    
    void excute(); //执行查询
    void queryIndexTable(); //查询索引
    void statistic(std::set<int> & iset);   //进行计算
    int distance(const std::string& rhs);
    void response(Cache & cache);

    void showQueue();   //test
private:
    std::string m_queryWord;
    int m_peerfd;
    std::priority_queue<MyResult, std::vector<MyResult>, MyCompare> m_resultQue;
};







}//end of namespace wd

