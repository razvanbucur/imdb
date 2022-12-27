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

    int choice;
    while (true)
    {
        /* sleep(2);
        std::cout << "\033[H\033[2J\033[3J";*/

        std::cout << "Enter choice:" << std::endl;
        std::cout << "1. Register\t\t2. Login\t\t0. Quit" << std::endl;
        std::cin >> choice;

        // std::cout << "\033[H\033[2J\033[3J";

        if (choice == 1) // definuri
        {
            bool couldRegister = Register();
            if (couldRegister == false)
            {
                Register();
            }
        }
        else if (choice == 2)
        {
            bool couldLogin = Login();
            if (couldLogin == false)
            {
                Login();
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
            StartApplication();
        }
    }

    client->StopClient(OPERATION_STOP);
}
void Application::ShowReturnMenu()
{
    char cont;
    do
    {
        std::cout << "Return to Main Menu? [Y/N]: ";
        std::cin >> cont;
        cont = toupper(cont);
        if (cont == 'Y')
        {
            break;
        }
        else if (cont == 'N')
        {
            std::cout << "Closing program..." << std::endl;

            exit(0);
        }
        else
        {
            std::cout << "Invalid choice!" << std::endl;
        }
    } while (cont != 'Y' || cont != 'N');
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
bool Application::Register()
{
    std::string email, password, name;

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

    std::string message = OPERATION_REGISTER "," + email + "," + password + "," + name;
    client->SendMessage(message); // to do: am trimis mesaj serverul il interpreteaza si-mi raspunde cu ceva,deci mai am de facut receive in client
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
    return false;
    // orice a fost initilizat static, de exemplu Client client = Client(54001), apelezi metode sau campuri din obiectul respectiv cu: client.metoda(); sau client.port. CU PUNCT
    // orice a fost initializat dinamic, de exemplu Client *client = new Client(54001), apelezi metode sau campuri din obiectul respectiv cu: client->metoda(); sau client->port. CU SAGEATA
}

bool Application::Login()
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
        return true;
    }
    else if (recvMessage == LOGIN_USER_PASS_INCORECT_CODE)
    {
        std::cout << LOGIN_USER_PASS_INCORECT_MESSAGE << std::endl;
    }
    return false;
}
