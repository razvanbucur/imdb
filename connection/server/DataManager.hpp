#pragma once
#include <vector>
#include <string>
#include "include/sqlite3pp/sqlite3pp.h"
#include <iostream>
#include "UUIDGenerator.hpp"
#include <algorithm>


#define DATABASE_PATH "/home/root/imdb/connection/server/databases/Log.db"

#define REG_SUCCESS_MESSAGE  "Registration successfully"
#define REG_INVALID_DATA_MESSAGE  "Invalid register data"
#define REG_INVALID_EMAIL_MESSAGE "Invalid email!"
#define REG_EMAIL_EXISTS_MESSAGE "Email already exists"
#define REG_INSECURE_PASS_MESSAGE "Insecure password"
#define REG_INVALID_NAME_MESSAGE "Invalid name!"
#define REG_INVALID_USERTYPE_MESSAGE "Invalid user type!"

#define LOGIN_SUCCESS_MESSAGE "Login successfull!"
#define LOGIN_USER_PASS_INCORECT_MESSAGE "Username or password incorect!"

#define STOP_MESSAGE  "The client has disconnected"
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

#define ACTOR_ADD_SUCCESS_MESSAGE "Actor added successfully!"

class DataManager

{
private:
    
    static bool IsSecurePassword(std::string password);
    static bool IsValidName(std::string name);
    static bool IsValidEmail(std::string email);
    static bool EmailExists(std::string email);
    static bool IsValidUserType(std::string userType);
    
public:
    DataManager();
    ~DataManager();

    static std::string RegisterUser(std::vector<std::string> splittedMessage);
    static std::string LoginUser(std::vector<std::string> splittedMessage);
    static std::string GetUserType(std::string email);
    static std::string SearchActor(std::string actorName);
    static std::string ActorAdd(std::string actorName);
};
