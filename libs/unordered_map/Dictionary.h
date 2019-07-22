#pragma once
#include <unordered_map>
#include <string>
#include <map>
#include <set>
#include <vector>
using std::set;
using std::vector;
using std::string;
using std::unordered_map;
using std::map;

class Dictionary
{
public:
    Dictionary() {}
    ~Dictionary() {}
    void buildDict(const string& fileName);
    void queryWord(const std::string& word);
    void saveToFile(const string& fileName);
protected:
    void DealOtherChar(string& str);
private:
    vector<string> m_lines;
    unordered_map<string, set<int>> m_word2line;  
    map<string, int> m_wordCnt;  
};

