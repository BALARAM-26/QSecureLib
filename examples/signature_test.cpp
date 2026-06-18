#include "signature.hpp"

#include <iostream>
#include <vector>

int main()
{
    std::vector<unsigned char> publicKey;
    std::vector<unsigned char> secretKey;

    std::vector<unsigned char> signature;

    std::vector<unsigned char> message =
    {
        'H','e','l','l','o'
    };

    Signature::generateKeyPair(
        publicKey,
        secretKey
    );

    Signature::sign(
        message,
        secretKey,
        signature
    );

    bool valid =
        Signature::verify(
            message,
            publicKey,
            signature
        );

    if(valid)
    {
        std::cout
            << "ML-DSA Success"
            << std::endl;
    }
    else
    {
        std::cout
            << "ML-DSA Failed"
            << std::endl;
    }

    return 0;
}
