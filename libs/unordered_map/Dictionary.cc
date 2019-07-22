#include "Dictionary.h"
#include "ctype.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
using std::cout;
using std::cin;
using std::endl;
using std::pair;
using std::ifstream;
using std::ofstream;
using std::istringstream;


void Dictionary::DealOtherChar(string& str)
{
    for(auto& ch : str)
    {
        if(!isalpha(ch))
        {
            ch = ' ';
        }else if(isupper(ch)){
            ch = tolower(ch);
        }
    }
}

void Dictionary::buildDict(const string& fileName)
{
    ifstream ifs(fileName);
    string line;
    int lineIndex = 0;
    while(getline(ifs, line))
    {
        m_lines.push_back(line);
        DealOtherChar(line);
        istringstream stream(line);
        string word;
        while(stream >> word)
        {
     //       cout << "word = " << word << endl;
            m_word2line[word].insert(lineIndex);
            ++m_wordCnt[word];
        }
        ++lineIndex;
    }
}

void Dictionary::queryWord(const std::string& word)
{
    if(m_word2line.find(word) != m_word2line.end())
    {
        cout << word << " occurs " << m_wordCnt[word] << 
            ((m_wordCnt[word] > 1) ? " times." : " time.") << endl;
        for(auto i = m_word2line[word].begin(); i != m_word2line[word].end(); ++i)
        {
            cout << "(line " << *i << ")  " << m_lines[*i] << endl;
        }
    }else{
        cout << "Don't find " << word << endl;
    }
}

bool compareCnt(const pair<string, int>& lhs, const pair<string, int>& rhs)
{
    return lhs.second > rhs.second;
}

void Dictionary::saveToFile(const string& fileName)
{
    ofstream ofs(fileName);
    vector<pair<string, int>> vecTmp(m_wordCnt.begin(), m_wordCnt.end());
    sort(vecTmp.begin(), vecTmp.end(), compareCnt);
    for(const auto& i : vecTmp)
    {
        ofs << i.first << " occurs " << i.second << 
            ((i.second > 1) ? " times." : " time.") << endl;
    }
}








