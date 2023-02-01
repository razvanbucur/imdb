#include "UUIDGenerator.hpp"
#include "include/uuid_v4/uuid_v4.h"

UUIDGenerator::UUIDGenerator()
{
}

UUIDGenerator::~UUIDGenerator()
{
}

std::string UUIDGenerator::Generate(std::string prefix){
    UUIDv4::UUIDGenerator<std::mt19937_64> uuidGenerator;
    UUIDv4::UUID uuid = uuidGenerator.getUUID();
    return prefix + "_" + uuid.str();
}