#include "Server.hpp"
#include "MessageInterpreter.hpp"


Server::Server(int listenPort)
{
    _listenPort = listenPort;
}

Server::~Server() {}

void Server::StartServer()
{

    CreateSocket();
    if (_listenSocket == -1)
    {
        return;
    }
    std::cout << "Socket was created" << std::endl;

    if (BindSocket() == 1)
    {
        return;
    }
    std::cout << "Bind was succesfull" << std::endl;

    if (StartListening() == 1)
    {
        return;
    }
    std::cout << "Listen was created" << std::endl;

    AcceptCall();
    if (_clientSocket == -1)
    {
        return;
    }
    std::cout << "Call was accepted" << std::endl;

    WhileReceiving();

    CloseSocket();
    std::cout << "Socket was closed" << std::endl;
}

void Server::CreateSocket()
{
    _listenSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (_listenSocket == -1)
    {
        std::cout << "Can't create a socket!" << std::endl;
    }
}

bool Server::BindSocket()
{
    sockaddr_in _settings;
    _settings.sin_family = DEFAULT_PROTOCOL;
    _settings.sin_port = htons(_listenPort);
    inet_pton(DEFAULT_PROTOCOL, DEFAULT_IP, &_settings.sin_addr);

    bool _couldBind = bind(_listenSocket, (sockaddr *)&_settings, sizeof(_settings));

    if (_couldBind == -1)
    {
        std::cout << "Can't bind socket to IP/port" << std::endl;
    }

    return _couldBind;
}

bool Server::StartListening()
{
    bool _couldListen = listen(_listenSocket, SOMAXCONN);
    if (_couldListen == -1)
    {
        std::cout << "Can't listen!" << std::endl;
    }
    return _couldListen;
}

void Server::AcceptCall()
{
    sockaddr_in client;
    socklen_t clientSize = sizeof(client);

    _clientSocket = accept(_listenSocket, (sockaddr *)&client, &clientSize);

    if (_clientSocket == -1)
    {

        std::cout << "Problem with client connecting!" << std::endl;
    }
}

void Server::WhileReceiving()
{
    char buff[4096];
    while (true)
    {

        memset(buff, 0, 4096);

        int bytesRecv = recv(_clientSocket, buff, 4096, 0);
        if (bytesRecv == -1)
        {

            std::cout << "There was a connection issue" << std::endl;
            break;
        }
        
        std::string message(buff);
        bool shouldStop = MessageInterpreter::InterpretMessage(message);
        if (shouldStop == true)
        {
            std::cout << "The client has disconnected" << std::endl;

            break;
        }
      
    }
}

void Server::CloseSocket()
{
    close(_clientSocket);
    close(_listenSocket);
}