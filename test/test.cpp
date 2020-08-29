
#include <iostream>
#include "TLSConnect.h"

#pragma comment(lib,"tlsConnect.lib")


int main()
{
    CTLSConnect* connect = new CTLSConnect(std::wstring(L"** URL **"));
    connect->open();
    connect->connect();
    connect->close();

}
