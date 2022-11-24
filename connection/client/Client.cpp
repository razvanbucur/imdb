#include "Client.hpp"
Client::Client(int listenPort)
{
    _listenPort = listenPort;
}
Client::~Client() {}

Client::Client() {}

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
    // While loop;

    char buf[4096];
    std::string userInput;

    do
    {
        // Enter lines of text
        std::cout << ">";
        std::getline(std::cin, userInput);

        _sendRes = send(_sock, userInput.c_str(), userInput.size() + 1, 0);

        if (_sendRes == -1)
        {
            break;
            std::cout << "Could not send to server!" << std::endl;
        }

        if (userInput == "stop" || userInput == " ")
        {

            std::cout << "Client and Server disconected!" << std::endl;
            break;
        }

        memset(buf, 0, 4096);
        int bytesReceived = recv(_sock, buf, 4096, 0);
        // Display response
        std::cout << "SERVER RESPONSE>";
        for (int x = 0; x < strlen(buf); x++)
            putchar(toupper(buf[x]));
        std::cout << std::endl;
    } while (true);

    // Close the socket
    close(_sock);
}
