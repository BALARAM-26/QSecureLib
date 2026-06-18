#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <string>
#include <vector>

class Container
{
public:

    static bool save(
        const std::string& filename,
        const std::vector<unsigned char>& kemCiphertext,
        const std::vector<unsigned char>& signature,
        const std::vector<unsigned char>& encryptedData
    );

    static bool load(
        const std::string& filename,
        std::vector<unsigned char>& kemCiphertext,
        std::vector<unsigned char>& signature,
        std::vector<unsigned char>& encryptedData
    );
};

#endif