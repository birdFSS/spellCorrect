#include "../include/SpellcorrectServer.h"


int main()
{
    //传入配置文件的路径
    wd::SpellcorrectServer scServer("../dictionary/conf/config.utf8");
    scServer.start();
    return 0;
}

