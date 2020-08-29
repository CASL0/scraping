#include "ScrapingUtility.h"
#include <fstream>
#include <iostream>
#include <string>

#pragma comment(lib,"ScrapingUtility.lib")
int main(void)
{
    std::ifstream ifs("file.html");
    if (!ifs)
    {
        std::cout << "ファイルが開けませんでした。" << std::endl;
        std::cin.get();
        return 0;
    }
    std::string data;
    std::string buf;
    while (!ifs.eof())
    {
        std::getline(ifs, buf);

        data += buf;
    }
    CScrapingUtility scr(data);
    scr.scraping();
}