#include "Server.hpp"

int main()
{
    Server server = Server(54001);
    server.StartServer();

    return 0;
}