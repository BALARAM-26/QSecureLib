#include "keymanager.hpp"
#include "aes_gcm.hpp"

#include <argon2.h>
#include <fstream>

std::vector<unsigned char>
KeyManager::deriveKey(
    const std::string& password)
{
    std::vector<unsigned char> key(32);

    const unsigned char salt[16] =
    {
        'Q','S','E','C',
        'U','R','E','L',
        'I','B','S','A',
        'L','T','0','1'
    };

    argon2id_hash_raw(
        2,
        65536,
        1,
        password.data(),
        password.size(),
        salt,
        sizeof(salt),
        key.data(),
        key.size()
    );

    return key;
}

bool KeyManager::saveKey(
    const std::string& filename,
    const std::vector<unsigned char>& key)
{
    std::ofstream file(
        filename,
        std::ios::binary
    );

    if (!file)
        return false;

    file.write(
        reinterpret_cast<const char*>(
            key.data()
        ),
        key.size()
    );

    return true;
}

std::vector<unsigned char>
KeyManager::loadKey(
    const std::string& filename)
{
    std::ifstream file(
        filename,
        std::ios::binary
    );

    if (!file)
        return {};

    file.seekg(
        0,
        std::ios::end
    );

    size_t size =
        static_cast<size_t>(
            file.tellg()
        );

    file.seekg(
        0,
        std::ios::beg
    );

    std::vector<unsigned char>
        key(size);

    file.read(
        reinterpret_cast<char*>(
            key.data()
        ),
        size
    );

    return key;
}

bool KeyManager::saveEncryptedKey(
    const std::string& filename,
    const std::vector<unsigned char>& key,
    const std::string& password)
{
    auto aesKey =
        deriveKey(password);

    auto encrypted =
        AESGCM::encrypt(
            key,
            aesKey
        );

    std::ofstream file(
        filename,
        std::ios::binary
    );

    if (!file)
        return false;

    uint32_t size =
        static_cast<uint32_t>(
            encrypted.size()
        );

    file.write(
        reinterpret_cast<const char*>(&size),
        sizeof(size)
    );

    file.write(
        reinterpret_cast<const char*>(
            encrypted.data()
        ),
        encrypted.size()
    );

    return true;
}

std::vector<unsigned char>
KeyManager::loadEncryptedKey(
    const std::string& filename,
    const std::string& password)
{
    auto aesKey =
        deriveKey(password);

    std::ifstream file(
        filename,
        std::ios::binary
    );

    if (!file)
        return {};

    uint32_t size = 0;

    file.read(
        reinterpret_cast<char*>(&size),
        sizeof(size)
    );

    std::vector<unsigned char>
        encrypted(size);

    file.read(
        reinterpret_cast<char*>(
            encrypted.data()
        ),
        size
    );

    return AESGCM::decrypt(
        encrypted,
        aesKey
    );
}