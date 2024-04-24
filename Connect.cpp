//
// Created by zyucidam on 2023/11/7.
//
#include"Connect.h"

void Connect::sperator()
{
    for(int i=0;i<28;i++) std::cout<<"=";
    std::cout<<" Initialize socket ";
    for(int i=0;i<28;i++) std::cout<<"=";
    std::cout<<std::endl;
}

void Connect::initSocket()
{
    //indicate window socket
    wsaData = WSADATA();
    if(0 != WSAStartup(MAKEWORD(2,2),&wsaData))
    {
    printf("Socket init ERROR");
    exit(1);
    }
    //initialize socket
    socketClient = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
}

Connect::Connect()
{
    initSocket();
    //create structure that stores server information
    memset(&serverInfor,0,sizeof serverInfor);
    serverInfor.sin_family = AF_INET;
    std::string IPAddress,portNumber;
    do{
        sperator();
        //input IP address and port number to the structure

        std::cout<<"input IP address : ";
        std::cin.sync();
        getline(std::cin,IPAddress);
        std::cout<<"input port number: ";
        std::cin.sync();
        getline(std::cin,portNumber);
        serverInfor.sin_addr.s_addr = inet_addr(IPAddress.data());
        serverInfor.sin_port = htons(atoi(portNumber.data()));

        if(portNumber != "16011")
        {
            std::cout<<"Error: connection is not built, try again"<<std::endl;
            continue;
        }
        //try to connect with server
        if(connect(socketClient,(struct sockaddr *)&serverInfor, sizeof(serverInfor)) == -1)
        {
            std::cout<<"Error: connection is not built, try again"<<std::endl;
            continue;
        } else {
            break;

        }
    } while(true);
}

void Connect::closeSocket()
{
    //close socket
    shutdown(socketClient,2);
    if(0 != WSACleanup()) {
        exit(1);
    }
}