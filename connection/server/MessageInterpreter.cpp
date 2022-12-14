#include "MessageInterpreter.hpp"
#include <string>
#include <vector>
#include <sstream>
#include "DataManager.hpp"

MessageInterpreter::MessageInterpreter()
{
}

MessageInterpreter::~MessageInterpreter()
{
}

std::vector<std::string> MessageInterpreter::SplitMessage(std::string message)
{
    char delimiter = ',';
    std::vector<std::string> splittedStringContent;
    std::string extractedString;
    std::istringstream messageStream(message);

    while (std::getline(messageStream, extractedString, delimiter))
    {
        splittedStringContent.push_back(extractedString);
    }
    return splittedStringContent;
}

bool MessageInterpreter::InterpretMessage(std::string message)
{
    // spargere mesaj dupa virgule
    // verificare primul element din mesaj, adica un cod pentru o anumita operatie/comanda (0 -> stop, 1 -> register, etc)
    std::vector<std::string> splittedMessage = SplitMessage(message);

    std::string currentOperation = splittedMessage[0];

    if (currentOperation == OPERATION_STOP)
    {
        return true;
    }
    else if (currentOperation == OPERATION_REGISTER)
    {
        DataManager::RegisterUser(splittedMessage);
    }
    else if (currentOperation == OPERATION_LOGIN)
    {
        DataManager::LoginUser(splittedMessage);
    }
}
