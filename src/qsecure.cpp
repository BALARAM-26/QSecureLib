#include "qsecure.hpp"
#include "filehandler.hpp"
#include "symmetric.hpp"
#include "aes_gcm.hpp"
#include "keymanager.hpp"

bool QSecure::encryptFile(
    const std::string& input,
    const std::string& output,
    const std::string& key)
{
    auto data = FileHandler::readFile(input);

    auto derivedKey =
        KeyManager::deriveKey(key);

    auto encrypted =
        AESGCM::encrypt(
            data,
            derivedKey
        );

    return FileHandler::writeFile(
        output,
        encrypted
    );
}

bool QSecure::decryptFile(
    const std::string& input,
    const std::string& output,
    const std::string& key)
{
    auto data = FileHandler::readFile(input);

    auto derivedKey =
        KeyManager::deriveKey(key);

    auto decrypted =
        AESGCM::decrypt(
            data,
            derivedKey
        );

    return FileHandler::writeFile(
        output,
        decrypted
    );
}