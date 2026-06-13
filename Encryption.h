#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <string>

// handles simple hashing of sensitive data like password and PIN
class Encryption {
private:
    static std::string key; // not used anymore in current hash version but kept for structure

public:
    // converts input string into a hashed numeric string (DJB2 hash)
    static std::string hash(std::string data);
};

#endif