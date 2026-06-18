#ifndef AES_GCM_HPP
#define AES_GCM_HPP

#include <vector>
#include <string>

class AESGCM
{
public:

    static std::vector<unsigned char>
    encrypt(
        const std::vector<unsigned char>& plaintext,
        const std::vector<unsigned char>& key
    );

    static std::vector<unsigned char>
    decrypt(
        const std::vector<unsigned char>& ciphertext,
        const std::vector<unsigned char>& key
    );
};

#endif