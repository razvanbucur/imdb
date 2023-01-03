#include <string>

#define UUID_PREFIX_USER "user"
#define UUID_PREFIX_ACTOR "actor"
#define UUID_PREFIX_MOVIE "movie"
#define UUID_PREFIX_DIRECTOR "director"
class UUIDGenerator
{
private:
    UUIDGenerator();
    ~UUIDGenerator();
public:
    static std::string Generate(std::string prefix);
};

