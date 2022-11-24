#include "Client.hpp"

int main()
{
    Client client = Client(54001);
    client.StartClient();

    return 0;
}
