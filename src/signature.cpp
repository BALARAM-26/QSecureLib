#include "signature.hpp"

#include <oqs/oqs.h>
#include <iostream>

bool Signature::generateKeyPair(
    std::vector<unsigned char>& publicKey,
    std::vector<unsigned char>& secretKey)
{
    OQS_SIG* sig =
        OQS_SIG_new(OQS_SIG_alg_ml_dsa_65);

    if (!sig)
    {
        std::cerr
            << "Failed to create ML-DSA object"
            << std::endl;

        return false;
    }

    publicKey.resize(
        sig->length_public_key
    );

    secretKey.resize(
        sig->length_secret_key
    );

    OQS_STATUS status =
        OQS_SIG_keypair(
            sig,
            publicKey.data(),
            secretKey.data()
        );

    OQS_SIG_free(sig);

    if (status != OQS_SUCCESS)
    {
        std::cerr
            << "ML-DSA key generation failed"
            << std::endl;

        return false;
    }

    std::cout
        << "ML-DSA keypair generated"
        << std::endl;

    return true;
}

bool Signature::sign(
    const std::vector<unsigned char>& message,
    const std::vector<unsigned char>& secretKey,
    std::vector<unsigned char>& signature)
{
    OQS_SIG* sig =
        OQS_SIG_new(OQS_SIG_alg_ml_dsa_65);

    if (!sig)
    {
        std::cerr
            << "Failed to create ML-DSA object"
            << std::endl;

        return false;
    }

    if (secretKey.size() != sig->length_secret_key)
    {
        std::cerr
            << "Invalid secret key size: "
            << secretKey.size()
            << " expected "
            << sig->length_secret_key
            << std::endl;

        OQS_SIG_free(sig);
        return false;
    }

    signature.resize(
        sig->length_signature
    );

    size_t sigLen = 0;

    OQS_STATUS status =
        OQS_SIG_sign(
            sig,
            signature.data(),
            &sigLen,
            message.data(),
            message.size(),
            secretKey.data()
        );

    std::cout
        << "Sign status = "
        << status
        << std::endl;

    std::cout
        << "Message size = "
        << message.size()
        << std::endl;

    std::cout
        << "Secret key size = "
        << secretKey.size()
        << std::endl;

    std::cout
        << "Signature length = "
        << sigLen
        << std::endl;

    signature.resize(sigLen);

    OQS_SIG_free(sig);

    return status == OQS_SUCCESS;
}

bool Signature::verify(
    const std::vector<unsigned char>& message,
    const std::vector<unsigned char>& publicKey,
    const std::vector<unsigned char>& signature)
{
    OQS_SIG* sig =
        OQS_SIG_new(OQS_SIG_alg_ml_dsa_65);

    if (!sig)
    {
        std::cerr
            << "Failed to create ML-DSA object"
            << std::endl;

        return false;
    }

    if (publicKey.size() != sig->length_public_key)
    {
        std::cerr
            << "Invalid public key size: "
            << publicKey.size()
            << " expected "
            << sig->length_public_key
            << std::endl;

        OQS_SIG_free(sig);
        return false;
    }

    OQS_STATUS status =
        OQS_SIG_verify(
            sig,
            message.data(),
            message.size(),
            signature.data(),
            signature.size(),
            publicKey.data()
        );

    std::cout
        << "Verify status = "
        << status
        << std::endl;

    std::cout
        << "Message size = "
        << message.size()
        << std::endl;

    std::cout
        << "Public key size = "
        << publicKey.size()
        << std::endl;

    std::cout
        << "Signature size = "
        << signature.size()
        << std::endl;

    OQS_SIG_free(sig);

    return status == OQS_SUCCESS;
}