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
    std::cout << "Do you want to be a normal user (0) or a moderator (1)?" << std::endl; 
    std::cin >> mod;

    std::string message = OPERATION_REGISTER "," + email + "," + password + "," + name + "," + mod; 
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
bool Application::ActorSearch()
{
    std::string actor;
    std::cout << "Which actor are you searching for" << std::endl;
    std::cin >> actor;
    sqlite3pp::database db(DATABASE_PATH);
    sqlite3pp::query qry(db, "SELECT Name FROM Actor");

    for (sqlite3pp::query::iterator i = qry.begin(); i != qry.end(); ++i)
    {

        for (int j = 0; j < qry.column_count(); ++j)
        {
            if (j == 0)
            {
                actor = (*i).get<char const *>(j);
            }
        }
        std::string clActor;

        clActor = actor;
        
        // logica de cautare
    }
    return false;
}
bool Application::DirectorSearch()
{
    std::string director;
    std::cout << "Which director are you searching for" << std::endl;
    std::cin >> director;
    sqlite3pp::database db(DATABASE_PATH);
    sqlite3pp::query qry(db, "SELECT Name FROM Director");

    for (sqlite3pp::query::iterator i = qry.begin(); i != qry.end(); ++i)
    {

        for (int j = 0; j < qry.column_count(); ++j)
        {
            if (j == 0)
            {
                director = (*i).get<char const *>(j);
            }
        }
        std::string clDirector;

        clDirector = director;
        // logica de cautare
    }
    return false;
}
bool Application::MovieSearch()
{
    std::string movie;
    std::cout << "Which movie are you searching for" << std::endl;
    std::cin >> movie;
    sqlite3pp::database db(DATABASE_PATH);
    sqlite3pp::query qry(db, "SELECT Name FROM Movie");

    for (sqlite3pp::query::iterator i = qry.begin(); i != qry.end(); ++i)
    {
        std::string movie;

        for (int j = 0; j < qry.column_count(); ++j)
        {
            if (j == 0)
            {
                movie = (*i).get<char const *>(j);
            }
        }
        std::string clMovie;

        clMovie = movie;

        // logica de cautare
    }
    return false;
}
std::string Application::AddActor()
{
    int actor;
    std::cout << "Enter actor!" << std::endl;
    std::cin >> actor;
    sqlite3pp::database db(DATABASE_PATH);

    sqlite3pp::command query(
        db, "INSERT INTO Actor (ID, Name) VALUES (?, ?)");
    query.binder() << UUIDGenerator::Generate(UUID_PREFIX_USER)
                   << actor;
    query.execute();
}
bool Application::Actor()
{
    int choice;
    std::cout << "Enter choice:" << std::endl;
    std::cout << "1. Search actor\t\t2. Add actor\t\t3. Delete actor by ID\t\t0. Quit" << std::endl;
    if (choice == 1)
    {
        ActorSearch();
    }
    else if (choice == 2)
    {
        AddActor();
    }
    else if (choice == 3)
    {
    std::string actor;
    std::cout << "Which actor you want to delete?" << std::endl;
    std::cin >> actor;
    sqlite3pp::database db(DATABASE_PATH);
    sqlite3pp::query qry(db, "DELETE FROM Actor WHERE Name='actor';");
        // logica de stergere
    }
    else if (choice == 0)
    {
        std::cout << "Closing program..." << std::endl;

        exit(0);
        // logica de quit
    }
    return false;
}
std::string Application::AddDirector()
{
    int director;
    std::cout << "Enter director!" << std::endl;
    std::cin >> director;
    sqlite3pp::database db(DATABASE_PATH); // server-send message sparta in fucntie pe server

    sqlite3pp::command query(
        db, "INSERT INTO Director (ID, Name) VALUES (?, ?)");

    query.binder() << UUIDGenerator::Generate(UUID_PREFIX_USER)
                   << director;
    query.execute();
}

bool Application::Director()
{
    int choice;
    std::cout << "Enter choice:" << std::endl;
    std::cin >> choice;
    std::cout << "1. Search director\t\t2. Add director\t\t3. Delete director by ID\t\t0. Quit" << std::endl;
    if (choice == 1)
    {
        DirectorSearch();
    }
    else if (choice == 2)
    {
        AddDirector();
    }
    else if (choice == 3)
    {
        std::string director;
    std::cout << "Which director you want to delete?" << std::endl;
    std::cin >> director;
    sqlite3pp::database db(DATABASE_PATH);
    sqlite3pp::query qry(db, "DELETE FROM Director WHERE Name='director';");
        // logica de stergere
    }
    else if (choice == 0)
    {
        std::cout << "Closing program..." << std::endl;

        exit(0);
        // logica de quit
    }
    return false;
}
std::string Application::AddMovie()
{
    int name, releaseDate, category;
    std::cout << "Enter movie name!" << std::endl;
    std::cin >> name;
    std::cout << "Enter release date!" << std::endl;
    std::cin >> releaseDate;
    std::cout << "Enter the category!" << std::endl;
    std::cin >> category;
    sqlite3pp::database db(DATABASE_PATH);

    sqlite3pp::command query(
        db, "INSERT INTO Movie (ID, Name, Release date, Category) VALUES (?, ?, ?, ?)");
    query.binder() << UUIDGenerator::Generate(UUID_PREFIX_USER)
                   << name
                   << releaseDate
                   << category;

    query.execute();
}

bool Application::Movie()
{
    int choice;
    std::cout << "Enter choice:" << std::endl;
    std::cin >> movie;
    std::cout << "1. Search movie\t\t2. Add movie\t\t3. Delete movie by ID\t\t0. Quit" << std::endl;
    if (choice == 1)
    {
        MovieSearch();
    }
    else if (choice == 2)
    {
        AddMovie();
    }
    else if (choice == 3)
    {
    std::string movie;
    std::cout << "Which movie you want to delete?" << std::endl;
    std::cin >> movie;
    sqlite3pp::database db(DATABASE_PATH);
    sqlite3pp::query qry(db, "DELETE FROM Movie WHERE Name='movie';");
        // logica de stergere
    }
    else if (choice == 0)
    {
        std::cout << "Closing program..." << std::endl;

        exit(0);
        // logica de quit
    }
    return false;
}

bool Application::ShowModeratorMenu()
{
    int actor, movie, director;
    int choice;
    std::cout << "Enter choice:" << std::endl;
    std::cout << "1. Actors\t\t2. Directors\t\t3. Movies\t\t0. Quit" << std::endl;
    std::cin >> choice;
    if (choice == 1)
    {
        Actor();
    }
    else if (choice == 2)
    {
        Director();
    }
    else if (choice == 3)
    {
        Movie();
    }
    else if (choice == 0)
    {
        std::cout << "Closing program..." << std::endl;

        exit(0);
        // logica de quit
    }

    return false;
}

bool Application::ShowUserMenu()
{

    int actor, movie, director;
    int choice;
    std::cout << "Enter choice:" << std::endl;
    std::cout << "1. Search actor\t\t2. Search director\t\t3. Search movie\t\t0. Quit" << std::endl;
    std::cin >> choice;

    if (choice == 1)
    {
        ActorSearch();
    }

    else if (choice == 2)
    {
        DirectorSearch();
    }
    else if (choice == 3)
    {
        MovieSearch();
        /* Search actor (pentru toţi utilizatorii)
         Search director (pentru toţi utilizatorii)
         Search movie (pentru toţi utilizatorii)*/
    }
    else if (choice == 0)
    {
        std::cout << "Closing program..." << std::endl;

        exit(0);
    }
    return false;
}

void Application::ModeratorOrNot(std::string userType)
{
    if (userType == "1")
    {
        ShowModeratorMenu();
    }
    else
    {
        ShowUserMenu();
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
