#include "asymmetric.hpp"

#include <iostream>

int main()
{
    std::vector<unsigned char> publicKey;
    std::vector<unsigned char> secretKey;

    std::vector<unsigned char> ciphertext;

    std::vector<unsigned char> sharedSecretA;
    std::vector<unsigned char> sharedSecretB;

    AsymmetricCrypto::generateKeyPair(
        publicKey,
        secretKey
    );

    AsymmetricCrypto::encapsulate(
        publicKey,
        ciphertext,
        sharedSecretA
    );

    AsymmetricCrypto::decapsulate(
        secretKey,
        ciphertext,
        sharedSecretB
    );

    if(sharedSecretA == sharedSecretB)
    {
        std::cout
            << "ML-KEM Success"
            << std::endl;
    }
    else
    {
        std::cout
            << "ML-KEM Failed"
            << std::endl;
    }

    return 0;
}