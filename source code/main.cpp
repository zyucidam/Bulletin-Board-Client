#include"Connect.h"
#include"Command.h"

#include<WinSock2.h>
#pragma comment(lib, "ws2_32.lib")


using namespace std;


int main()
{
    //initialize socket and connect to server
    Connect myConnect = Connect();
    //send command and receive message from server
    Command myCommand = Command(myConnect.getSocket(),myConnect.getSock());
    //close socket
    myConnect.closeSocket();
}