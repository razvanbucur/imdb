#include <string>
#include <vector>

#define OPERATION_STOP "0"
#define OPERATION_REGISTER "1"
#define OPERATION_LOGIN "2"

class MessageInterpreter
{
private:
    static std::vector<std::string> SplitMessage(std::string message);
public:
    MessageInterpreter();
    ~MessageInterpreter();
    static bool InterpretMessage(std::string message);
};
