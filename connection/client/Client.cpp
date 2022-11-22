#include "Client.hpp"
Client::Client(int listenPort) {
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
    
}

void Client::CreateSocket()
{
    int sock = socket(DEFAULT_PROTOCOL, SOCK_STREAM, 0);
}

void Client::HintStructure()
{
    std::string ipAddress = DEFAULT_IP;
    hint.sin_family = DEFAULT_PROTOCOL;
    hint.sin_port = htons(_listenPort);
    inet_pton(DEFAULT_PROTOCOL, ipAddress.c_str(), &hint.sin_addr);
}

void Client::ConnectServer()
{
    _connectRes = connect(_sock, (sockaddr *)&hint, sizeof(hint));
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
            std::cout << "Could not send to server!";

            continue;
        }

        memset(buf, 0, 4096);
        int bytesReceived = recv(_sock, buf, 4096, 0);
        // Display response
        std::cout << "SERVER>" << std::string(buf, bytesReceived) << "\r\n";
     } while (true);
            
        // Close the socket
        close(_sock);
    
}