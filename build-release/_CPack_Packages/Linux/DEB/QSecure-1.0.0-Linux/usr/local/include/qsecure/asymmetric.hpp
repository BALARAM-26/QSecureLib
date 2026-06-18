#ifndef ASYMMETRIC_HPP
#define ASYMMETRIC_HPP

#include <vector>

class AsymmetricCrypto
{
public:

    static bool generateKeyPair(
        std::vector<unsigned char>& publicKey,
        std::vector<unsigned char>& secretKey
    );

    static bool encapsulate(
        const std::vector<unsigned char>& publicKey,
        std::vector<unsigned char>& ciphertext,
        std::vector<unsigned char>& sharedSecret
    );

    static bool decapsulate(
        const std::vector<unsigned char>& secretKey,
        const std::vector<unsigned char>& ciphertext,
        std::vector<unsigned char>& sharedSecret
    );
};

#endif