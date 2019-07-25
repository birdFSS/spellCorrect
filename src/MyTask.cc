#include "../include/MyTask.h"
#include "../include/MyDict.h"
#include <iostream>
using std::cout;
using std::endl;
using std::string;

namespace wd
{
size_t nBytesCode(const char ch);
std::size_t length(const std::string &str);
int editDistance(const std::string & lhs, const std::string &rhs);

int triple_min(const int &a, const int &b, const int &c)
{
	return a < b ? (a < c ? a : c) : (b < c ? b : c);
}

void MyTask::showQueue()
{
    cout << " MyTask::showQueue()" << endl;
    cout << m_queryWord << endl;
    int i = 0;
    while(i++ < 10 && m_resultQue.size() > 0)
    {
        MyResult elem = m_resultQue.top();
        m_resultQue.pop();
        cout << "word = " << elem.m_word << "  frequency = " << elem.m_freq << "  distance =  " << elem.m_dist << endl;
    }

}

void MyTask::excute()
{
    queryIndexTable();
    response();
}

void MyTask::queryIndexTable()
{
    MyDict* pDict = MyDict::getInstance();
    auto& m_indexTable = pDict->getIndexTable();    
    pDict->showTableInTestFile();

    int len = length(m_queryWord);
    int pos = 0;
    int step = nBytesCode(m_queryWord[0]);
    auto iter = m_indexTable.begin();
    for(int i=0; i< len; i++)
    {
        string oneWord(m_queryWord, pos, step);
        cout << oneWord << endl;
        if((iter = m_indexTable.find(oneWord)) != m_indexTable.end())
        {
            statistic(iter->second);
        }
        pos += step;
    }
}

void MyTask::statistic(std::set<int> & iset)
{
    auto iter = iset.begin();
    int dist;

    MyDict* pDict = MyDict::getInstance();
    auto & m_dict = pDict->getDict();

    while(iter != iset.end())
    {
        dist = distance(m_dict[*iter].first);
        m_resultQue.push(MyResult(m_dict[*iter].first, m_dict[*iter].second, dist));
        ++iter;
    }
}

int MyTask::distance(const std::string & rhs)
{
    return editDistance(m_queryWord, rhs);
}

void MyTask::response()
{
    string msg;
    int i = 3;
    while(i-- != 0 && m_resultQue.size() != 0)
    {
        string tmp = m_resultQue.top().m_word;
        m_resultQue.pop();
        msg = msg + " " + tmp;
    }
    m_conn->sendInLoop(msg);
}


/// 获取一个字节高位开头为1的个数
size_t nBytesCode(const char ch)
{
	if(ch & (1 << 7))
	{
		int nBytes = 1;
		for(int idx = 0; idx != 6; ++idx)
		{
			if(ch & (1 << (6 - idx)))
			{
				++nBytes;	
			}
			else
				break;
		}
		return nBytes;
	}
	return 1;
}  
  

std::size_t length(const std::string &str)
{
	std::size_t ilen = 0;
	for(std::size_t idx = 0; idx != str.size(); ++idx)
	{
		int nBytes = nBytesCode(str[idx]);
		idx += (nBytes - 1);
		++ilen;
	}
	return ilen;
}


int editDistance(const std::string & lhs, const std::string &rhs)
{//计算最小编辑距离-包括处理中英文
	size_t lhs_len = length(lhs);
	size_t rhs_len = length(rhs);
	int editDist[lhs_len + 1][rhs_len + 1];
	for(size_t idx = 0; idx <= lhs_len; ++idx)
	{
		editDist[idx][0] = idx;
	}

	for(size_t idx = 0; idx <= rhs_len; ++idx)
	{
		editDist[0][idx] = idx;
	}
	
	std::string sublhs, subrhs;
	for(std::size_t dist_i = 1, lhs_idx = 0; dist_i <= lhs_len; ++dist_i, ++lhs_idx)
	{
		size_t nBytes = nBytesCode(lhs[lhs_idx]);
		sublhs = lhs.substr(lhs_idx, nBytes);
		lhs_idx += (nBytes - 1);

		for(std::size_t dist_j = 1, rhs_idx = 0; dist_j <= rhs_len; ++dist_j, ++rhs_idx)
		{
			nBytes = nBytesCode(rhs[rhs_idx]);
			subrhs = rhs.substr(rhs_idx, nBytes);
			rhs_idx += (nBytes - 1);
			if(sublhs == subrhs)
			{
				editDist[dist_i][dist_j] = editDist[dist_i - 1][dist_j - 1];
			}
			else
			{
				editDist[dist_i][dist_j] = triple_min(
					editDist[dist_i][dist_j - 1] + 1,
					editDist[dist_i - 1][dist_j] + 1,
					editDist[dist_i - 1][dist_j - 1] + 1);
			}
		}
	}
	return editDist[lhs_len][rhs_len];
}















}//wd
