#include "MessageInterpreter.hpp"


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

std::string MessageInterpreter::InterpretMessage(std::string message)
{
    // spargere mesaj dupa virgule
    // verificare primul element din mesaj, adica un cod pentru o anumita operatie/comanda (0 -> stop, 1 -> register, etc)
    std::vector<std::string> splittedMessage = SplitMessage(message);

    std::string currentOperation = splittedMessage[0];
    std::string returnValue;
    if (currentOperation == OPERATION_STOP)
    {
        returnValue = STOP_CODE;
    }
    else if (currentOperation == OPERATION_REGISTER)
    {
        returnValue = DataManager::RegisterUser(splittedMessage);
    }
    else if (currentOperation == OPERATION_LOGIN)
    {
        returnValue = DataManager::LoginUser(splittedMessage);
    } else if (currentOperation == OPERATION_GET_USERTYPE) {
        returnValue = DataManager::GetUserType(splittedMessage[1]);
    }
    return returnValue;
}
