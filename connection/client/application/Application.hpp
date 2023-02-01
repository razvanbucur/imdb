#include "../Client.hpp"
#include <utility>
#include <iostream>
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <unistd.h>
#include <termios.h>

#define DATABASE_PATH "/home/root/imdb/connection/server/databases/Log.db"

#define OPERATION_STOP "0"
#define OPERATION_REGISTER "1"
#define OPERATION_LOGIN "2"
#define OPERATION_GET_USERTYPE "3"
#define OPERATION_ACTOR_SEARCH "4"
#define OPERATION_ACTOR_ADD "5"
#define OPERATION_DIRECTOR_ADD "6"
#define OPERATION_MOVIE_ADD "7"
#define OPERATION_DIRECTOR_SEARCH "8"
#define OPERATION_MOVIE_SEARCH "9"

#define OPERATION_ACTOR_DELETE "10"
#define OPERATION_DIRECTOR_DELETE "11"
#define OPERATION_MOVIE_DELETE "12"

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
    void ShowActorSearchMenu();
    void ShowDirectorSearchMenu();
    void ShowMovieSearchMenu();
    void ShowActorChoiceMenu();
    void ShowDirectorChoiceMenu();
    void ShowMovieChoiceMenu();
    void ShowAddMovieMenu();
    void ShowAddDirectorMenu();
    void ShowAddActorMenu();
    void ShowDeleteActorMenu();
    void ShowDeleteDirectorMenu();
    void ShowDeleteMovieMenu();


public:

    Application();
    ~Application();
    void StartApplication();
};
