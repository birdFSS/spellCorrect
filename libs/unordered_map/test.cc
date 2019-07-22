#include "Dictionary.h"
#include <iostream>

using std::endl;
using std::cout;
int main(int argc, char* argv[])
{
    Dictionary d1;

    d1.buildDict("../The_Holy_Bible.txt");
    if(argc == 2)
    {
        d1.queryWord(argv[1]);
    }
    d1.saveToFile("ffh.txt");
    return 0;
}

