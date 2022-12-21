#include "Server.hpp"

int main()
{

    Server server = Server(54001);
    while (true)
    {
        server.StartServer();
    }
    return 0;
}