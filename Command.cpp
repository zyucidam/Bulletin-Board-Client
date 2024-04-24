//
// Created by zyucidam on 2023/11/7.
//

#include"Command.h"

void Command::sperator(std::string str)
{
    for(int i=0;i<30;i++) std::cout<<"=";
    std::cout<<str;
    for(int i=0;i<30;i++) std::cout<<"=";
    std::cout<<std::endl;
}

void Command::sendMsg(std::string sendStr)
{
    send(socketClient,sendStr.data(),sendStr.size(),0) ;

}

int Command::recvMsg()
{
    int k = recv(socketClient,buf,10000,0);
    for(int i=0;i<k;i++) std::cout<<buf[i];
    std::cout<<std::endl;
    return k;
}

int Command::getMsg()
{
    int k = recv(socketClient,buf,10000,0);
    strBuf = (buf);
    strBuf = strBuf.replace(strBuf.find("server"),6,"client");
    for(int i=0;i<k;i++) std::cout<<strBuf[i];
    std::cout<<std::endl;
    return k;
}

Command::Command(SOCKET sc,struct sockaddr_in ms)
{
    mySock = ms;
    buf = new char[10000];
    this->socketClient = sc;
    sperator(" Input command ");
    while(true)
    {
        std::cout<<"Input command:";
        std::string cmd;
        std::cin.sync();
        getline(std::cin,cmd);
        sendMsg(cmd);
        if(cmd == "EXIT")
        {
            recvMsg();
            break;

        } else if (cmd == "POST_STRING") {

            sperator(" Content (Type a long '&' to end message) ");
            std::string content;
            int timer = 0;
            do{
                timer++;
                std::cout<<"client: ";
                std::cin>>content;
                sendMsg(content);
            } while (content != "&");
            //if receive message return -1, then error happen
            if(recvMsg() < 0)
            {
                std::cout<<"---"<<std::endl;
                std::cout<<"Sent "<<timer<<" messages to (IP address:"<<inet_ntoa(mySock.sin_addr)<<", port number:16011)\n";
                std::cout<<"Connect status: ERROR\nSend status: ERROR\n";
                std::cout<<"---"<<std::endl;
            } else {
                std::cout<<"---"<<std::endl;
                std::cout<<"Sent "<<timer<<" messages to (IP address:"<<inet_ntoa(mySock.sin_addr)<<", port number:16011)\n";
                std::cout<<std::endl<<"Connect status: OK\nSend status: OK\n";
                std::cout<<"---"<<std::endl;
            }

        } else if (cmd == "GET") {

            std::cout<<"---Received Messages---"<<std::endl;
            int n;
            //continue messages until error happen or receive &
            do {
                n = getMsg() - 1;
            }while(n >= -1 && strBuf[n] != '&');

            std::cout<<"(IP address:"<<inet_ntoa(mySock.sin_addr)<<", port number:16011)\n";
            if(n < -1)
            {
                std::cout<<"Connect status: ERROR\nSend status: ERROR\n";
            } else {
                std::cout<<std::endl<<"Connect status: OK\nSend status: OK\n";
            }

        } else if (cmd == "POST_FILE") {

            recvMsg();
            std::cout<<"client: ";
            std::string pathname;
            std::cin.sync();
            getline(std::cin,pathname);

            //check file exist or not
            if(access(pathname.c_str(),F_OK) == -1)
            {
                std::cout<<"Cannot find the file"<<std::endl;
                sendMsg("close");
                recvMsg();
            } else {
                //get filesize
                struct stat statbuf;
                stat(pathname.c_str(),&statbuf);
                int fileSize = statbuf.st_size;

                //get filename from pathname
                std::string filename = pathname.substr(pathname.rfind(R"(\)")+1,pathname.size() -1 );

                //from a header file which contain filename and filesize using 128sl format
                char fhead[128 + sizeof(long)];
                memset(fhead,0,sizeof(fhead));
                memcpy(fhead, filename.c_str(), filename.size());
                memcpy(fhead + 128, &fileSize, sizeof(long));

                //if filesize larger than 256 then ERROR
                if(fileSize > 256)
                {
                    std::cout<<"File larger than 256 bytes"<<std::endl;
                    sendMsg("close");
                    recvMsg();
                } else {
                    std::cout<<"Transfer file absolute path : "<<pathname<<std::endl;
                    //send header file to server
                    send(socketClient,fhead,sizeof (fhead),0);
                    //open file
                    std::ifstream file(pathname, std::ios::binary);
                    char buffer[20];
                    //send message to server until file is all read or ERROR happen
                    while(file.read(buffer,sizeof(buffer)))
                    {
                        if(send(socketClient,buffer,sizeof(buffer),0) < 0)
                        {
                            std::cout<<"Send failed"<<std::endl;
                        }
                    }
                    file.close();
                    recvMsg();
                }

            }
        } else {
            //if cmd is not POST_STRING,POST_FILE,EXIT,GET receive messages and input another command
            recvMsg();
        }

        sperator("next command");

    }
}