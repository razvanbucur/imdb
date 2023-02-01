#include "Server.hpp"

int main()
{

    Server server = Server(54001);
bool couldStartServer = true;
    while (couldStartServer)
    {
        couldStartServer = server.StartServer();
    }
    return 0;
}