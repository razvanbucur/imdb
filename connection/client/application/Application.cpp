#include "Application.hpp"
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <unistd.h>

Application::Application()
{
}
Application::~Application()
{
}
void Application::StartApplication()
{

    int choice;
    while (true)
    {
        sleep(2);
        std::cout << "\033[H\033[2J\033[3J";

        std::cout << "Enter choice:" << std::endl;
        std::cout << "1. Register\t\t2. Login\t\t3. Quit" << std::endl;
        std::cin >> choice;

        std::cout << "\033[H\033[2J\033[3J";
        
        if (choice == 1)
        {
            Register();
        }
        else if (choice == 2)
        {
            Login();
        }
        else if (choice == 3)
        {
            std::cout << "You stopped the application." << std::endl;
            break;
        }
        else
        {
            break;
            std::cout << "Please enter a valid choice!" << std::endl;
        }
    }
}

void Application::Register()
{
    std::string uName, pass, name, email;

    std::ofstream output;
    output.open("record.txt");
    std::cout << "Enter username: " << std::endl;
    std::cin >> uName;
    std::cout << "Enter password: " << std::endl;
    std::cin >> pass;
    std::cout << "Enter name: " << std::endl;
    std::cin >> name;
    std::cout << "Enter email: " << std::endl;
    std::cin >> email;

    output << uName << " " << pass << " " << name << " " << email << std::endl;
    output.close();
    std::cout << "Registration complete!" << std::endl;
}
void Application::Login()
{
    std::string uName, pass;
    std::string logname, logpass;
    std::string valname, valpass;

    //  login
    std::ifstream input("record.txt");

    if (!input)
    {
        std::cout << "Error creating account!";
    }

    std::cout << "Enter username:" << std::endl;
    std::cin >> logname;
    std::cout << "Enter password:" << std::endl;
    std::cin >> logpass;

//  LOGIN USER PAROLA
// RASPUNS DE LA SERVER OK SAU NO_OK

// IF OK => LOGIN SUCCES ELSE FAIL
    if (input >> uName && input >> pass && // verificat daca contul este inregistrat
        uName == logname && pass == logpass)
    {
        std::cout << "Login successful" << std::endl;
    }
    else
    {
        std::cout << "Login failed!" << std::endl;
    }

    input.close();
    std::cout << "Done!" << std::endl;
}
