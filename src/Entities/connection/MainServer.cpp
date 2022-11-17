#include "Server.hpp"

int main()
{
    Server server = Server(10000);
    server.StartServer();

    return 0;
}