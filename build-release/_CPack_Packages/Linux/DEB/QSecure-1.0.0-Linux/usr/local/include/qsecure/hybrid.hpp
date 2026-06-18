#ifndef HYBRID_HPP
#define HYBRID_HPP

#include <string>
#include <vector>

class HybridCrypto
{
public:

    static bool encryptFile(
        const std::string& inputFile,
        const std::string& outputFile,
        const std::vector<unsigned char>& publicKey
    );

    static bool decryptFile(
        const std::string& inputFile,
        const std::string& outputFile,
        const std::vector<unsigned char>& secretKey
    );
};

#endif