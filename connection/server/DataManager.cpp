#include "DataManager.hpp"

DataManager::DataManager()
{
}

DataManager::~DataManager()
{
}

std::string DataManager::RegisterUser(std::vector<std::string> splittedMessage)
{
    if (splittedMessage.size() != 4)
    {

        std::cout << REG_INVALID_DATA_MESSAGE << std::endl;
        return REG_INVALID_DATA_CODE;
    }

    if (!IsValidEmail(splittedMessage[1]))
    {
        std::cout << REG_INVALID_EMAIL_MESSAGE << std::endl;
        return REG_INVALID_EMAIL_CODE;
    }
    if (EmailExists(splittedMessage[1]))
    {
        std::cout << REG_EMAIL_EXISTS_MESSAGE << std::endl;
        return REG_EMAIL_EXISTS_CODE;
    }
    if (!IsSecurePassword(splittedMessage[2]))
    {
        std::cout << REG_INSECURE_PASS_MESSAGE << std::endl;
        return REG_INSECURE_PASS_CODE;
    }
    if (!IsValidName(splittedMessage[3]))
    {
        std::cout << REG_INVALID_NAME_MESSAGE << std::endl;
        return REG_INVALID_NAME_CODE;
    }

    sqlite3pp::database db(DATABASE_PATH);

    sqlite3pp::command query(
        db, "INSERT INTO Users (ID, Email, Password, Name, Mod) VALUES (?, ?, ?, ?, ?)");
    query.binder() << UUIDGenerator::Generate(UUID_PREFIX_USER)
                   << splittedMessage[1]
                   << splittedMessage[2]
                   << splittedMessage[3]
                   << splittedMessage[4];
    query.execute();

    std::cout << REG_SUCCESS_MESSAGE << std::endl;
    return REG_SUCCESS_CODE;
}
bool DataManager::ModeratorORNot(std::string mod)
{
    if (mod == "moderator")
    {
        ShowModeratorMenu();
    }
    else if (mod == "user")
    {
        ShowUserMenu(); /// show user main menu (numele functiei) + plus cele de la actor director etc
    }
    return false;
}

bool DataManager::ActorSearch(std::string)
{
    std::cout << "Which actor are you searching for" << std::endl;
    sqlite3pp::database db(DATABASE_PATH);
    sqlite3pp::query qry(db, "SELECT Name FROM Actor");

    for (sqlite3pp::query::iterator i = qry.begin(); i != qry.end(); ++i)
    {
        std::string actor;

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
bool DataManager::DirectorSearch(std::string)
{
    std::cout << "Which director are you searching for" << std::endl;
    sqlite3pp::database db(DATABASE_PATH);
    sqlite3pp::query qry(db, "SELECT Name FROM Director");

    for (sqlite3pp::query::iterator i = qry.begin(); i != qry.end(); ++i)
    {
        std::string director;

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
bool DataManager::MovieSearch(std::string)
{
    std::cout << "Which movie are you searching for" << std::endl;
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

bool DataManager::Actor(std::string)
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
        int actor;
        std::cout << "Enter actor!" << std::endl;
        sqlite3pp::database db(DATABASE_PATH);

        sqlite3pp::command query(
            db, "INSERT INTO Actor (ID, Name) VALUES (?, ?)");
        query.binder() << UUIDGenerator::Generate(UUID_PREFIX_USER)
                       << actor;

        query.execute();
    }
    else if (choice == 3)
    {
        
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
bool DataManager::Director(std::string)
{
    int choice;
    std::cout << "Enter choice:" << std::endl;
    std::cout << "1. Search director\t\t2. Add director\t\t3. Delete director by ID\t\t0. Quit" << std::endl;
    if (choice == 1)
    {
        DirectorSearch();
    }
    else if (choice == 2)
    {
        int director;
        std::cout << "Enter director!" << std::endl;
        sqlite3pp::database db(DATABASE_PATH);

        sqlite3pp::command query(
            db, "INSERT INTO Director (ID, Name) VALUES (?, ?)");
        query.binder() << UUIDGenerator::Generate(UUID_PREFIX_USER)
                       << director;

        query.execute();
    }
    else if (choice == 3)
    {
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
bool DataManager::Movie(std::string)
{
    int choice;
    std::cout << "Enter choice:" << std::endl;
    std::cout << "1. Search movie\t\t2. Add movie\t\t3. Delete movie by ID\t\t0. Quit" << std::endl;
    if (choice == 1)
    {
        MovieSearch();
    }
    else if (choice == 2)
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
    else if (choice == 3)
    {

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

bool DataManager::ShowModeratorMenu(std::string)
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
    /*actor
    Search actor (pentru toţi utilizatorii)
    Add actor (doar pentru moderatori)
    Remove actor (doar pentru moderatori)
    director
    Search director (pentru toţi utilizatorii)
    Add director (doar pentru moderatori)
    Remove director (doar pentru moderatori)
    movie
    Search movie (pentru toţi utilizatorii)
    Add movie (doar pentru moderatori)
    Remove movie (doar pentru moderatori)*/
    return false;
}

bool DataManager::ShowUserMenu(std::string)
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

bool DataManager::IsValidName(std::string name)
{
    if (name.empty())
    {

        return false;
    }
    if (std::find_if(name.begin(), name.end(), ::isdigit) != name.end())
    {

        return false;
    }
    return true;
}

bool DataManager::IsSecurePassword(std::string password)
{
    if (password.size() < 7)
    {
        return false;
    }
    if (std::find_if(password.begin(), password.end(), ::isdigit) == password.end())
    {
        return false;
    }

    return true;
}

// nume@yahoo.com
// nume.nume@yahoocom
// string@string.string regex

bool DataManager::IsValidEmail(std::string email)
{
    if (email.find("@") == std::string::npos)
    {
        return false;
    }
    if (email.find(".") == std::string::npos)
    {
        return false;
    }
    return true;
}
bool DataManager::EmailExists(std::string email)
{
    sqlite3pp::database db(DATABASE_PATH);
    sqlite3pp::query qry(db, "SELECT Email FROM Users");

    for (sqlite3pp::query::iterator k = qry.begin(); k != qry.end(); ++k)
    {

        std::string dbEmailReg = (*k).get<std::string>(0);

        if (email == dbEmailReg)
        {
            return true;
        }
    }
    return false;
}

std::string DataManager::LoginUser(std::vector<std::string> splittedMessage)

{
    sqlite3pp::database db(DATABASE_PATH);
    sqlite3pp::query qry(db, "SELECT Email,Password FROM Users");

    for (sqlite3pp::query::iterator i = qry.begin(); i != qry.end(); ++i)
    {
        std::string dbEmail, dbPassword;

        for (int j = 0; j < qry.column_count(); ++j)
        {
            if (j == 0)
            {
                dbEmail = (*i).get<char const *>(j);
            }
            if (j == 1)
            {
                dbPassword = (*i).get<char const *>(j);
            }
        }
        std::string clEmail, clPassword;

        clEmail = splittedMessage[1];
        clPassword = splittedMessage[2];

        if (clEmail == dbEmail && clPassword == dbPassword)
        {
            std::cout << LOGIN_SUCCESS_MESSAGE << std::endl;
            return LOGIN_SUCCESS_CODE;
        }
    }

    std::cout << LOGIN_USER_PASS_INCORECT_MESSAGE << std::endl;
    return LOGIN_USER_PASS_INCORECT_CODE;
}
