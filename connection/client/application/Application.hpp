#include "../Client.hpp"
#include <utility>
#include "include/sqlite3pp/sqlite3pp.h"
#include <iostream>
#include "UUIDGenerator.hpp"

#define OPERATION_STOP "0"
#define OPERATION_REGISTER "1"
#define OPERATION_LOGIN "2"
#define OPERATION_GET_USERTYPE "3"
#define APP_STOP "You stopped the application."
#define VALID_CHOICE "Please enter a valid choice!"


#define REG_SUCCESS_MESSAGE "Registration successfully"
#define REG_INVALID_DATA_MESSAGE "Invalid register data"
#define REG_INVALID_EMAIL_MESSAGE "Invalid email!"
#define REG_EMAIL_EXISTS_MESSAGE "Email already exists"
#define REG_INSECURE_PASS_MESSAGE "Insecure password"
#define REG_INVALID_NAME_MESSAGE "Invalid name!"
#define REG_INVALID_USERTYPE_MESSAGE "Invalid user type!"

#define LOGIN_SUCCESS_MESSAGE "Login successful!"
#define LOGIN_USER_PASS_INCORECT_MESSAGE "Username or password incorect!"

#define STOP_MESSAGE "The client has disconnected"
#define STOP_CODE "-1"

#define REG_SUCCESS_CODE "0"
#define REG_INVALID_DATA_CODE "1"
#define REG_INVALID_EMAIL_CODE "2"
#define REG_EMAIL_EXISTS_CODE "3"
#define REG_INSECURE_PASS_CODE "4"
#define REG_INVALID_NAME_CODE "5"
#define REG_INVALID_USERTYPE_CODE "6"

#define LOGIN_SUCCESS_CODE "0"
#define LOGIN_USER_PASS_INCORECT_CODE "1"

class Application
{
private:
    Client *client;
    void ShowHomeMenu();
    std::pair<bool, std::string> ShowLoginMenu();
    bool ShowRegisterMenu();
    char getch();
    std::string GetUserType(std::string email);
    void ModeratorOrNot(std::string userType);
    void ShowUserMenu();
    void ShowModeratorMenu();
    bool ActorSearch();
    bool DirectorSearch():
    bool MovieSearch();
    bool Actor();
    bool Director();
    bool Movie();
    std::string AddMovie();
    std::string AddDirector();
    std::string AddActor();



public:

    Application();
    ~Application();
    void StartApplication();
};
