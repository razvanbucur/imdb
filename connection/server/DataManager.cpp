#include "DataManager.hpp"

DataManager::DataManager()
{
}

DataManager::~DataManager()
{
}

bool DataManager::RegisterUser(std::vector<std::string> splittedMessage)
{
    if (splittedMessage.size() != 4)
    {

        std::cout << "Invalid register data" << std::endl;
        return false;
    }

    if (!IsValidEmail(splittedMessage[1]))
    {
        std::cout << "Invalid email!" << std::endl;
        return false;
    }
    if (!IsSecurePassword(splittedMessage[2]))
    {
        std::cout << "Insecure password!" << std::endl;
        return false;
    }
    if (!IsValidName(splittedMessage[3]))
    {
        std::cout << "Invalid name!" << std::endl;
        return false;
    }

    sqlite3pp::database db(DATABASE_PATH);

    sqlite3pp::command query(
        db, "INSERT INTO Users (ID, Email, Password, Name) VALUES (?, ?, ?, ?)");
    query.binder() << UUIDGenerator::Generate(UUID_PREFIX_USER)
                   << splittedMessage[1]
                   << splittedMessage[2]
                   << splittedMessage[3];

    query.execute();
    std::cout<< "Registration successfully!"<< std::endl;
    
    return true;
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

bool DataManager::LoginUser(std::vector<std::string> splittedMessage)
{
    return true;
}