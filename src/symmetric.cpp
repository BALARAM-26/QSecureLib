#include "symmetric.hpp"

std::vector<unsigned char>
SymmetricCrypto::encrypt(
    const std::vector<unsigned char>& data,
    const std::string& key)
{
    std::vector<unsigned char> result = data;

    for(size_t i = 0; i < result.size(); i++)
    {
        result[i] ^= key[i % key.size()];
    }

    return result;
}

std::vector<unsigned char>
SymmetricCrypto::decrypt(
    const std::vector<unsigned char>& data,
    const std::string& key)
{
    return encrypt(data, key);
}