#include "DataManager.hpp"

DataManager::DataManager()
{
}

DataManager::~DataManager()
{
}

std::string DataManager::RegisterUser(std::vector<std::string> splittedMessage)
{
    if (splittedMessage.size() != 5)
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
    if (!IsValidUserType(splittedMessage[4]))
    {
        std::cout << REG_INVALID_USERTYPE_MESSAGE << std::endl;
        return REG_INVALID_USERTYPE_CODE;
    }

    sqlite3pp::database db(DATABASE_PATH);

    sqlite3pp::command query(
        db, "INSERT INTO Users (ID, Email, Password, Name, UserType) VALUES (?, ?, ?, ?, ?)");
    query.binder() << UUIDGenerator::Generate(UUID_PREFIX_USER)
                   << splittedMessage[1]
                   << splittedMessage[2]
                   << splittedMessage[3]
                   << splittedMessage[4];
    query.execute();

    std::cout << REG_SUCCESS_MESSAGE << std::endl;
    return REG_SUCCESS_CODE;
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

bool DataManager::IsValidUserType(std::string userType)
{
    if (userType == "0" || userType == "1")
    {
        return true;
    }
    return false;
}

std::string DataManager::LoginUser(std::vector<std::string> splittedMessage)
{
    sqlite3pp::database db(DATABASE_PATH);
    sqlite3pp::query qry(db, "SELECT Email,Password,UserType FROM Users");

    for (sqlite3pp::query::iterator i = qry.begin(); i != qry.end(); ++i)
    {
        std::string dbEmail, dbPassword, userType;

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
            std::string message = LOGIN_SUCCESS_CODE "," + userType;
            return LOGIN_SUCCESS_CODE;
        }
    }

    std::cout << LOGIN_USER_PASS_INCORECT_MESSAGE << std::endl;
    return LOGIN_USER_PASS_INCORECT_CODE;
}

std::string DataManager::GetUserType(std::string email) {
    sqlite3pp::database db(DATABASE_PATH);
    sqlite3pp::query qry(db, "SELECT Email,UserType FROM Users");

    for (sqlite3pp::query::iterator i = qry.begin(); i != qry.end(); ++i)
    {
        std::string dbEmail, dbUserType;
        for (int j = 0; j < qry.column_count(); ++j)
        {
            if (j == 0)
            {
                dbEmail = (*i).get<char const *>(j);
            }
            if (j == 1)
            {
                dbUserType = (*i).get<char const *>(j);
            }

        }
        if (email == dbEmail)
        {
            return dbUserType;
        }
    }
    return "0";
}
