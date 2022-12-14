#include <vector>
#include <string>
#include "include/sqlite3pp/sqlite3pp.h"
#include <iostream>
#include "UUIDGenerator.hpp"
#include <algorithm>

#define DATABASE_PATH "/home/root/imdb/connection/server/databases/Log.db"

class DataManager

{
private:
    static bool IsSecurePassword(std::string password);
    static bool IsValidName(std::string name);
    static bool IsValidEmail(std::string email);
public:
    DataManager();
    ~DataManager();

    static bool RegisterUser(std::vector<std::string> splittedMessage);
    static bool LoginUser(std::vector<std::string> splittedMessage);
};
