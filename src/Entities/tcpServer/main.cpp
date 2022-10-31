#include <iostream>
#include <string>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include "..//Actor.hpp"
#include "..//Director.hpp"
#include "..//User.hpp"
#include "../Movie.hpp"

using namespace std;

int main()
{
    // Create a socket
    int listening = socket(AF_INET, SOCK_STREAM, 0);
    if (listening == -1)
    {
        std::cerr << "Can't create a socket!";
        return -1;
    }

    // Bind the socket to a IP / port
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(54000);
    inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);

    if (bind(listening, (sockaddr *)&hint, sizeof(hint)) == -1)
    {
        std::cerr << " Can't bind to IP/port";
        return -2;
    }
    // Mark the socket for listening in

    if (listen(listening, SOMAXCONN) == -1)
    {

        cerr << "Can't listen!";
        return -3;
    }

    // Accept a call

    sockaddr_in client;
    socklen_t clientSize = sizeof(client);
    char host[NI_MAXHOST];
    char svc[NI_MAXSERV];

    int clientSocket = accept(listening, (sockaddr *)&client, &clientSize);

    if (clientSocket == -1)
    {

        cerr << "Problem with client connecting!";

        return -4;
    }

    // Close the listening socket

    close(listening);

    memset(host, 0, NI_MAXHOST);
    memset(svc, 0, NI_MAXSERV);

    int result = getnameinfo((sockaddr *)&client, sizeof(client), host, NI_MAXHOST, svc, NI_MAXSERV, 0);

    if (result)
    {

        std::cout << host << "Connected" << svc << endl;
    }
    else
    {
        inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
        std::cout << host << "CONNECTED ON" << ntohs(client.sin_port) << endl;
    }

    // While receiving - display message,echo message

    char buff[4096];
    while (true)
    {
        // Clear the buffer
        memset(buff, 0, 4096);
        // Wait for message
        int bytesRecv = recv(clientSocket, buff, 4096, 0);
        if (bytesRecv == -1)
        {

            std::cerr << "There was a connection issue" << endl;
            break;
        }
        if (bytesRecv == 0)
        {
            cout << "The client is connected" << endl;
            break;
        }
        // Display message
        std::cout << "Received: " << string(buff, 0, bytesRecv) << endl;
        // Resend message
        send(clientSocket, buff, bytesRecv + 1, 0);
    }

    // Close the socket
    close(clientSocket);
    return 0;
}
