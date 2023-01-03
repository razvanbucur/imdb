#pragma once

#include <string>
#include <vector>
#include <sstream>
#include "DataManager.hpp"

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

class MessageInterpreter
{
private:
    static std::vector<std::string> SplitMessage(std::string message);
public:
    MessageInterpreter();
    ~MessageInterpreter();
    static std::string InterpretMessage(std::string message);
};
