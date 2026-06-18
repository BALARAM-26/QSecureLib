#include "asymmetric.hpp"
#include "keymanager.hpp"

#include <iostream>

int main()
{
    std::vector<unsigned char> publicKey;
    std::vector<unsigned char> privateKey;

    AsymmetricCrypto::generateKeyPair(
        publicKey,
        privateKey
    );

    KeyManager::saveKey(
        "../keys/alice.pub",
        publicKey
    );

    KeyManager::saveKey(
        "../keys/alice.priv",
        privateKey
    );

    // Load keys back
    auto loadedPublicKey =
        KeyManager::loadKey(
            "../keys/alice.pub"
        );

    auto loadedPrivateKey =
        KeyManager::loadKey(
            "../keys/alice.priv"
        );

    std::cout
        << "Public Key Size: "
        << loadedPublicKey.size()
        << std::endl;

    std::cout
        << "Private Key Size: "
        << loadedPrivateKey.size()
        << std::endl;

    return 0;
}