#include <string>

#define UUID_PREFIX_USER "user"

class UUIDGenerator
{
private:
    UUIDGenerator();
    ~UUIDGenerator();
public:
    static std::string Generate(std::string prefix);
};

