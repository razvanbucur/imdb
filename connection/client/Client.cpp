#include "Client.hpp"

Client::Client(int listenPort)
{
    _listenPort = listenPort;
}
Client::~Client() {}

void Client::StartClient()
{
    CreateSocket();
    if (_sock == -1)
    {
        return;
    };
    std::cout << "Socket was created" << std::endl;
    HintStructure();
    ConnectServer();
    if (_connectRes == -1)
    {
        std::cout << "Connection not possible!" << std::endl;
    }
}

void Client::StopClient(std::string closingMessage) {
    SendMessage(closingMessage);
    CloseSocket();
}

void Client::CreateSocket()
{
    _sock = socket(DEFAULT_PROTOCOL, SOCK_STREAM, 0);
}

void Client::HintStructure()
{
    std::string ipAddress = DEFAULT_IP;
    _settings.sin_family = DEFAULT_PROTOCOL;
    _settings.sin_port = htons(_listenPort);
    inet_pton(DEFAULT_PROTOCOL, ipAddress.c_str(), &_settings.sin_addr);
}

void Client::ConnectServer()
{
    _connectRes = connect(_sock, (sockaddr *)&_settings, sizeof(_settings));
    if (_connectRes == -1)
    {
        return;
    }
}
void Client::SendMessage(std::string message)
{
    _sendRes = send(_sock, message.c_str(), message.size() + 1, 0);

    if (_sendRes == -1)
    {

        std::cout << "Could not send to server!" << std::endl;
    }
}
void Client::CloseSocket()
{
    close(_sock);
}