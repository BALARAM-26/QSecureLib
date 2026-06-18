#include "hybrid.hpp"

#include "filehandler.hpp"
#include "aes_gcm.hpp"
#include "asymmetric.hpp"

#include <cstdint>
#include <cstring>

bool HybridCrypto::encryptFile(
    const std::string& inputFile,
    const std::string& outputFile,
    const std::vector<unsigned char>& publicKey)
{
    // Read original file
    auto plaintext =
        FileHandler::readFile(inputFile);

    if (plaintext.empty())
    {
        return false;
    }

    // ML-KEM
    std::vector<unsigned char> kemCiphertext;
    std::vector<unsigned char> sharedSecret;

    if (!AsymmetricCrypto::encapsulate(
            publicKey,
            kemCiphertext,
            sharedSecret))
    {
        return false;
    }

    // AES-GCM using shared secret
    auto encryptedData =
        AESGCM::encrypt(
            plaintext,
            sharedSecret
        );

    // File format:
    // [4 bytes kem size]
    // [kem ciphertext]
    // [aes encrypted data]

    std::vector<unsigned char> output;

    uint32_t kemSize =
        static_cast<uint32_t>(
            kemCiphertext.size()
        );

    unsigned char sizeBytes[4];

    std::memcpy(
        sizeBytes,
        &kemSize,
        sizeof(kemSize)
    );

    output.insert(
        output.end(),
        sizeBytes,
        sizeBytes + 4
    );

    output.insert(
        output.end(),
        kemCiphertext.begin(),
        kemCiphertext.end()
    );

    output.insert(
        output.end(),
        encryptedData.begin(),
        encryptedData.end()
    );

    return FileHandler::writeFile(
        outputFile,
        output
    );
}

bool HybridCrypto::decryptFile(
    const std::string& inputFile,
    const std::string& outputFile,
    const std::vector<unsigned char>& secretKey)
{
    auto input =
        FileHandler::readFile(inputFile);

    if (input.size() < 4)
    {
        return false;
    }

    uint32_t kemSize = 0;

    std::memcpy(
        &kemSize,
        input.data(),
        sizeof(kemSize)
    );

    if (input.size() < 4 + kemSize)
    {
        return false;
    }

    std::vector<unsigned char> kemCiphertext(
        input.begin() + 4,
        input.begin() + 4 + kemSize
    );

    std::vector<unsigned char> encryptedData(
        input.begin() + 4 + kemSize,
        input.end()
    );

    std::vector<unsigned char> sharedSecret;

    if (!AsymmetricCrypto::decapsulate(
            secretKey,
            kemCiphertext,
            sharedSecret))
    {
        return false;
    }

    auto plaintext =
        AESGCM::decrypt(
            encryptedData,
            sharedSecret
        );

    if (plaintext.empty())
    {
        return false;
    }

    return FileHandler::writeFile(
        outputFile,
        plaintext
    );
}