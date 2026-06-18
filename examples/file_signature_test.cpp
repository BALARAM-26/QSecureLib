#include "filehandler.hpp"
#include "signature.hpp"

#include <iostream>

int main()
{
    std::vector<unsigned char> publicKey;
    std::vector<unsigned char> privateKey;

    Signature::generateKeyPair(
        publicKey,
        privateKey
    );

    auto fileData =
        FileHandler::readFile(
            "../sample.txt"
        );

    std::vector<unsigned char> signature;

    Signature::sign(
        fileData,
        privateKey,
        signature
    );

    bool valid =
        Signature::verify(
            fileData,
            publicKey,
            signature
        );

    if(valid)
    {
        std::cout
            << "File Signature Valid"
            << std::endl;
    }
    else
    {
        std::cout
            << "File Signature Invalid"
            << std::endl;
    }

    return 0;
}