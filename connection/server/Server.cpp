#include "Server.hpp"

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
        std::cout << "Can't create a socket!" << std::endl;
        return;
    }

    std::cout << "Socket was created" << std::endl;

    if (BindSocket() == 1)
    {
        std::cout << "Can't bind socket to IP/port" << std::endl;
        return;
    }
    std::cout << "Bind was succesfull" << std::endl;

    if (StartListening() == 1)
    {
        std::cout << "Can't listen!" << std::endl;
        return;
    }
    std::cout << "Listen was created" << std::endl;

    AcceptCall();
    if (_clientSocket == -1)
    {
        std::cout << "Problem with client connecting!" << std::endl;
        return;
    }
    std::cout << "Call was accepted" << std::endl;

    WhileReceiving();

    CloseListenSocket();
    std::cout << "Socket was closed" << std::endl;
}

void Server::CreateSocket()
{
    _listenSocket = socket(AF_INET, SOCK_STREAM, 0);
}

bool Server::BindSocket()
{
    sockaddr_in _settings;
    _settings.sin_family = DEFAULT_PROTOCOL;
    _settings.sin_port = htons(_listenPort);
    inet_pton(DEFAULT_PROTOCOL, DEFAULT_IP, &_settings.sin_addr);

    bool _couldBind = bind(_listenSocket, (sockaddr *)&_settings, sizeof(_settings));

    return _couldBind;
}

bool Server::StartListening()
{
    bool _couldListen = listen(_listenSocket, SOMAXCONN);

    return _couldListen;
}

void Server::AcceptCall()
{
    sockaddr_in client;
    socklen_t clientSize = sizeof(client);

    _clientSocket = accept(_listenSocket, (sockaddr *)&client, &clientSize);
}

void Server::WhileReceiving()
{
    char buff[4096];
    while (true)
    {
        memset(buff, 0, 4096);

        int bytesRecv = recv(_clientSocket, buff, 4096, 0); // alex0000000000000 la primul 0 se opreste deoarece acolo se termina sirul de caractere
        if (bytesRecv == -1)
        {
            std::cout << "There was a connection issue" << std::endl;
            CloseClientSocket();
            break;
        }

        std::string message(buff);

        std::string returnValue = MessageInterpreter::InterpretMessage(message);
        if (returnValue == STOP_CODE)
        {
            CloseClientSocket();
            std::cout << STOP_MESSAGE << std::endl;
            continue;
        }
        SendMessage(returnValue);
    }
}

void Server::SendMessage(std::string message)
{
    int sendRes = send(_clientSocket, message.c_str(), message.size() + 1, 0);

    if (sendRes == -1)
    {

        std::cout << "Could not send to client!" << std::endl;
    }
}

void Server::CloseListenSocket()
{

    close(_listenSocket);
}
void Server::CloseClientSocket()
{
    close(_clientSocket);
}