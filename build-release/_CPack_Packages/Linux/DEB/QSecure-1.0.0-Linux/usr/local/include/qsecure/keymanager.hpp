#ifndef KEYMANAGER_HPP
#define KEYMANAGER_HPP

#include <string>
#include <vector>

class KeyManager
{
public:

    static std::vector<unsigned char>
    deriveKey(
        const std::string& password
    );

    static bool saveKey(
        const std::string& filename,
        const std::vector<unsigned char>& key
    );

    static std::vector<unsigned char>
    loadKey(
        const std::string& filename
    );
};

#endif