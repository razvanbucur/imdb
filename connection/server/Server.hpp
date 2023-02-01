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

// Bubble sort

// void Bubble()
// {
//     std::vector<int> v { 4, 12, 6, 25, 3 };

//     for (int i = 0; i < v.size(); i++)
//     {
//         for (int j = 0; j < v.size(); j++)
//         {
//             if (v[i] < v[j])
//             {
//                 int temp = v[i];
//                 v[i] = v[j];
//                 v[j] = temp;
//             }
//         }
            
//         }
//         for (int i = 0; i < v.size(); i++){
//     std::cout<< v[i]<<" ";
        
//     }
// }

// int main()
// {
//   Bubble();
    
//     return 0;
// }

// // Selection sort

