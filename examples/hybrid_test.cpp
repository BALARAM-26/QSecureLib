#include "asymmetric.hpp"
#include "hybrid.hpp"

#include <iostream>

int main()
{
    std::vector<unsigned char> publicKey;
    std::vector<unsigned char> secretKey;

    if (!AsymmetricCrypto::generateKeyPair(
            publicKey,
            secretKey))
    {
        std::cout << "Key generation failed\n";
        return 1;
    }

    if (!HybridCrypto::encryptFile(
            "../sample.txt",
            "sample.qsec",
            publicKey))
    {
        std::cout << "Encryption failed\n";
        return 1;
    }

    if (!HybridCrypto::decryptFile(
            "sample.qsec",
            "sample_dec.txt",
            secretKey))
    {
        std::cout << "Decryption failed\n";
        return 1;
    }

    std::cout
        << "Hybrid Encryption Success"
        << std::endl;

    return 0;
}