#include "../include/Configutation.h"
#include "../include/DictProducer.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;

int main()
{
    wd::DictProducer dict("../conf/english.txt");
    dict.setIgnoreWords("../conf/ignore.txt");
    dict.buildDict();
    //dict.showDict();
    dict.storeDict("../data/dict_test.txt");
    return 0;
}

