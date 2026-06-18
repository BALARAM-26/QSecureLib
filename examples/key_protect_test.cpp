#include "keymanager.hpp"
#include <iostream>

int main()
{
    std::vector<unsigned char>
        key =
        {1,2,3,4,5};

    bool ok =
        KeyManager::saveEncryptedKey(
            "secret.key",
            key,
            "mypassword"
        );

    if(!ok)
    {
        std::cout
            << "Save failed\n";

        return 1;
    }

    auto loaded =
        KeyManager::loadEncryptedKey(
            "secret.key",
            "mypassword"
        );

    std::cout
        << "Loaded size = "
        << loaded.size()
        << std::endl;

    return 0;
}