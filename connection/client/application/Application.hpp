#include "../Client.hpp"

#define OPERATION_STOP "0"
#define OPERATION_REGISTER "1"
#define OPERATION_LOGIN "2"

class Application
{
private:
    Client *client;
public:
    Application();
    ~Application();
    void StartApplication();
    void Login();
    void Register();
};
