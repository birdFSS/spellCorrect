#pragma once
#include "SplitTool.h"
#include "cppjieba/Jieba.hpp"

namespace wd
{

const char* const DICT_PATH = "../source/dict/jieba.dict.utf8";
const char* const HMM_PATH = "../source/dict/hmm_model.utf8";
const char* const USER_DICT_PATH = "../source/dict/user.dict.utf8";
const char* const IDF_PATH = "../source/dict/idf.utf8";                                                                                                                                         
const char* const STOP_WORD_PATH = "../source/dict/stop_words.utf8";

class CppJieba :
    public SplitTool
{
public:
    CppJieba() : m_jieba(DICT_PATH,
                HMM_PATH,
                USER_DICT_PATH,
                IDF_PATH,
                STOP_WORD_PATH)
    {}
    ~CppJieba() {}
    std::vector<std::string> cut(const std::string & sentence) override
    {
        std::vector<std::string> words;
        m_jieba.Cut(sentence, words, true);
        return words;
    }
private:
    cppjieba::Jieba m_jieba;
};




}//end of namespace wd

