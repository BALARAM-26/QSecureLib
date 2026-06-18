#ifndef SYMMETRIC_HPP
#define SYMMETRIC_HPP

#include <vector>
#include <string>

class SymmetricCrypto
{
public:

    static std::vector<unsigned char>
    encrypt(
        const std::vector<unsigned char>& data,
        const std::string& key
    );

    static std::vector<unsigned char>
    decrypt(
        const std::vector<unsigned char>& data,
        const std::string& key
    );
};

#endif