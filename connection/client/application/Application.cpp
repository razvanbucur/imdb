#include "Application.hpp"
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <unistd.h>
#include <termios.h>

Application::Application()
{
    client = new Client(54001);
}

Application::~Application()
{
    delete client;
}

void Application::StartApplication()
{
    client->StartClient();

    ShowHomeMenu();

    client->StopClient(OPERATION_STOP);
}

void Application::ShowHomeMenu()
{
    while (true)
    {
        /* sleep(2);
        std::cout << "\033[H\033[2J\033[3J";*/

        std::cout << "Enter choice:" << std::endl;
        std::cout << "1. Register\t\t2. Login\t\t0. Quit" << std::endl;

        int choice;
        std::cin >> choice;

        if (choice == 1) // definuri
        {
            while (true)
            {
                bool couldRegister = ShowRegisterMenu();
                if (couldRegister)
                {
                    break;
                }
                else
                {
                    std::cout << "Do you want to try again? [Y/N]: ";
                    char input;
                    std::cin >> input;
                    input = toupper(input);
                    if (input == 'Y')
                    {
                        continue;
                    }
                    else if (input == 'N')
                    {
                        break;
                    }
                    else
                    {
                        std::cout << "Invalid choice!" << std::endl;
                    }
                }
            }
        }
        else if (choice == 2)
        {
            while (true)
            {
                std::pair<bool, std::string> loginOutput = ShowLoginMenu();
                bool couldLogin = loginOutput.first;
                if (couldLogin)
                {
                    ModeratorOrNot(loginOutput.second);
                }
                else
                {
                    std::cout << "Do you want to try again? [Y/N]: ";
                    char input;
                    std::cin >> input;
                    input = toupper(input);
                    if (input == 'Y')
                    {
                        continue;
                    }
                    else if (input == 'N')
                    {
                        break;
                    }
                    else
                    {
                        std::cout << "Invalid choice!" << std::endl;
                    }
                }
            }
        }
        else if (choice == 0)
        {
            std::cout << APP_STOP << std::endl;
            break;
        }
        else
        {
            std::cout << VALID_CHOICE << std::endl;
        }
    }
}

char Application::getch()
{

    char buf = 0;
    struct termios old = {0};
    fflush(stdout);
    if (tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON; // local modes = Non Canonical mode
    old.c_lflag &= ~ECHO;   // local modes = Disable echo.
    old.c_cc[VMIN] = 1;     // control chars (MIN value) = 1
    old.c_cc[VTIME] = 0;    // control chars (TIME value) = 0 (No time)
    if (tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if (read(0, &buf, 1) < 0)
        perror("read()");
    old.c_lflag |= ICANON; // local modes = Canonical mode
    old.c_lflag |= ECHO;   // local modes = Enable echo.
    if (tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
    return buf;
}

bool Application::ShowRegisterMenu()
{
    std::string email, password, name, mod;

    std::cout << "Enter email: " << std::endl;
    std::cin >> email;
    std::cout << "Enter password: " << std::endl;
    int ch = getch();
    while (ch != 10)
    {
        password.push_back(ch);
        std::cout << 'x';
        ch = getch();
    }
    std::cout << std::endl;
    std::cout << "Enter name: " << std::endl;
    std::cin >> name;
    std::cout << "Do you want to be a normal user (0) or a moderator (1)?" << std::endl; // 1 sau 2
    std::cin >> mod;

    std::string message = OPERATION_REGISTER "," + email + "," + password + "," + name + "," + mod; // verificat mod
    client->SendMessage(message);
    std::string recvMessage = client->ReceiveMessage();

    if (recvMessage == REG_SUCCESS_CODE)
    {
        std::cout << REG_SUCCESS_MESSAGE << std::endl;
        return true;
    }
    else if (recvMessage == REG_INVALID_DATA_CODE)
    {
        std::cout << REG_INVALID_DATA_MESSAGE << std::endl;
    }
    else if (recvMessage == REG_INVALID_EMAIL_CODE)
    {
        std::cout << REG_INVALID_EMAIL_MESSAGE << std::endl;
    }
    else if (recvMessage == REG_EMAIL_EXISTS_CODE)
    {
        std::cout << REG_EMAIL_EXISTS_MESSAGE << std::endl;
    }
    else if (recvMessage == REG_INSECURE_PASS_CODE)
    {
        std::cout << REG_INSECURE_PASS_MESSAGE << std::endl;
    }
    else if (recvMessage == REG_INVALID_NAME_CODE)
    {
        std::cout << REG_INVALID_NAME_MESSAGE << std::endl;
    }
    else if (recvMessage == REG_INVALID_USERTYPE_CODE)
    {
        std::cout << REG_INVALID_USERTYPE_MESSAGE << std::endl;
    }
    return false;
    // orice a fost initilizat static, de exemplu Client client = Client(54001), apelezi metode sau campuri din obiectul respectiv cu: client.metoda(); sau client.port. CU PUNCT
    // orice a fost initializat dinamic, de exemplu Client *client = new Client(54001), apelezi metode sau campuri din obiectul respectiv cu: client->metoda(); sau client->port. CU SAGEATA
}

std::pair<bool, std::string> Application::ShowLoginMenu()
{

    std::string logname, logpass;

    // login
    std::cout << "Enter email:" << std::endl;
    std::cin >> logname;
    std::cout << "Enter password:" << std::endl;
    int ch = getch();
    while (ch != 10)
    {
        logpass.push_back(ch);
        std::cout << 'x';
        ch = getch();
    }
    std::cout << std::endl;

    std::string message = OPERATION_LOGIN "," + logname + "," + logpass;
    client->SendMessage(message);

    std::string recvMessage = client->ReceiveMessage();
    if (recvMessage == LOGIN_SUCCESS_CODE)
    {
        std::cout << LOGIN_SUCCESS_MESSAGE << std::endl;
        std::string userType = GetUserType(logname);
        return std::make_pair(true, userType);
    }
    else if (recvMessage == LOGIN_USER_PASS_INCORECT_CODE)
    {
        std::cout << LOGIN_USER_PASS_INCORECT_MESSAGE << std::endl;
    }
    return std::make_pair(false, "");
}

std::string Application::GetUserType(std::string email)
{
    std::string message = OPERATION_GET_USERTYPE "," + email;
    client->SendMessage(message);
    std::string userType = client->ReceiveMessage();

    return userType;
}

void Application::ModeratorOrNot(std::string userType)
{
    if (userType == "1")
    {
        ShowModeratorMenu();
    }
    else
    {
        ShowUserMenu(); /// show user main menu (numele functiei) + plus cele de la actor director etc
    }
}
void Application::ShowModeratorMenu()
{
    int actor, movie, director;
    int choice;
    std::cout << "Enter choice:" << std::endl;
    std::cout << "1. Actors\t\t2. Directors\t\t3. Movies\t\t0. Quit" << std::endl;
    std::cin >> choice;
    if (choice == 1)
    {
        std::cout << "Actor()" << std::endl;
    }
    else if (choice == 2)
    {
        std::cout << "Director();" << std::endl;
    }
    else if (choice == 3)
    {
        std::cout << "Movie();" << std::endl;
    }
    else if (choice == 0)
    {
        std::cout << "Closing program..." << std::endl;

        exit(0);
        // logica de quit
    }
}

void Application::ShowUserMenu()
{

    int actor, movie, director;
    int choice;
    std::cout << "Enter choice:" << std::endl;
    std::cout << "1. Search actor\t\t2. Search director\t\t3. Search movie\t\t0. Quit" << std::endl;
    std::cin >> choice;

    if (choice == 1)
    {
        std::cout << "ActorSearch();" << std::endl;
    }

    else if (choice == 2)
    {
        std::cout << "DirectorSearch();" << std::endl;
    }
    else if (choice == 3)
    {
        std::cout << "MovieSearch();    " << std::endl;
    }
    else if (choice == 0)
    {
        std::cout << "Closing program..." << std::endl;

        exit(0);
    }
}
