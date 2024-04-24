//
// Created by zyucidam on 2023/11/7.
//

#ifndef UNTITLED_COMMAND_H
#define UNTITLED_COMMAND_H

#endif //UNTITLED_COMMAND_H

#include<winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#include<iostream>
#include<string.h>
#include<string>
#include<sys/stat.h>
#include<unistd.h>
#include <fstream>

class Command
{
private:
    SOCKET socketClient;
    struct sockaddr_in mySock;
    char* buf;
    std::string strBuf;
public:
    Command(SOCKET sc,struct sockaddr_in my);
    void sperator(std::string str);
    void sendMsg(std::string sendStr);
    int recvMsg();
    int getMsg();
};