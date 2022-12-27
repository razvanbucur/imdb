#include "../Client.hpp"

#define OPERATION_STOP "0"
#define OPERATION_REGISTER "1"
#define OPERATION_LOGIN "2"
#define APP_STOP "You stopped the application."
#define VALID_CHOICE "Please enter a valid choice!"


#define REG_SUCCESS_MESSAGE "Registration successfully"
#define REG_INVALID_DATA_MESSAGE "Invalid register data"
#define REG_INVALID_EMAIL_MESSAGE "Invalid email!"
#define REG_EMAIL_EXISTS_MESSAGE "Email already exists"
#define REG_INSECURE_PASS_MESSAGE "Insecure password"
#define REG_INVALID_NAME_MESSAGE "Invalid name!"

#define LOGIN_SUCCESS_MESSAGE "Login successfull!"
#define LOGIN_USER_PASS_INCORECT_MESSAGE "Username or password incorect!"

#define STOP_MESSAGE "The client has disconnected"
#define STOP_CODE "-1"

#define REG_SUCCESS_CODE "0"
#define REG_INVALID_DATA_CODE "1"
#define REG_INVALID_EMAIL_CODE "2"
#define REG_EMAIL_EXISTS_CODE "3"
#define REG_INSECURE_PASS_CODE "4"
#define REG_INVALID_NAME_CODE "5"

#define LOGIN_SUCCESS_CODE "0"
#define LOGIN_USER_PASS_INCORECT_CODE "1"

class Application
{
private:
    Client *client;

public:
    Application();
    ~Application();
    void StartApplication();
    bool Login();
    bool Register();
    char getch();
    void ShowReturnMenu();
};
