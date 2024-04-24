//
// Created by zyucidam on 2023/11/7.
//

#ifndef UNTITLED_CONNECT_H
#define UNTITLED_CONNECT_H

#endif //UNTITLED_CONNECT_H

#include<WinSock2.h>
#pragma comment(lib, "ws2_32.lib")
#include<iostream>
#include<cstring>

class Connect
{
private:
    WSADATA wsaData;
    SOCKET socketClient;
    struct sockaddr_in serverInfor;

public:
    Connect();

    sockaddr_in getSock() {return serverInfor;}

    SOCKET getSocket() {return socketClient;}

    void sperator();

    void initSocket();

    void closeSocket();
};