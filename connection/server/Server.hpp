#pragma once
#include <iostream>
#include <string>
#include <cstring>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "MessageInterpreter.hpp"

#define DEFAULT_PROTOCOL AF_INET
#define DEFAULT_IP "127.0.0.1"

class Server 
{
private:

    int _listenPort;
    int _listenSocket;
    int _clientSocket;
    
    void CreateSocket();
    bool BindSocket();
    bool StartListening();
    void AcceptCall();
    void CloseListening();
    void WhileReceiving();  
    void SendMessage(std::string message);
    void CloseListenSocket();
    void CloseClientSocket();
public:
    Server(int listenPort);
    ~Server();

    bool StartServer();
};
