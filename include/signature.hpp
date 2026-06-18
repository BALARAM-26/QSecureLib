#ifndef SIGNATURE_HPP
#define SIGNATURE_HPP

#include <vector>

class Signature
{
public:

    static bool generateKeyPair(
        std::vector<unsigned char>& publicKey,
        std::vector<unsigned char>& secretKey
    );

    static bool sign(
        const std::vector<unsigned char>& message,
        const std::vector<unsigned char>& secretKey,
        std::vector<unsigned char>& signature
    );

    static bool verify(
        const std::vector<unsigned char>& message,
        const std::vector<unsigned char>& publicKey,
        const std::vector<unsigned char>& signature
    );
};

#endif