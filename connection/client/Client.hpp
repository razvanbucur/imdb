#include <iostream>
#include <string>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>

#define DEFAULT_PROTOCOL AF_INET
#define DEFAULT_IP "127.0.0.1"
#define MESSAGE_NOT_RECEIVED "Message not received"

class Client
{
private:
    int _sock;
    int _sendRes;
    int _connectRes;
    sockaddr_in _settings;
    int _listenPort;

    void CreateSocket();
    void HintStructure();
    void ConnectServer();
    void CloseSocket();

public:
    Client(int listenPort);
    ~Client();
    void StartClient();
    void StopClient(std::string closingMessage);
    void SendMessage(std::string message);
    std::string ReceiveMessage();
};
