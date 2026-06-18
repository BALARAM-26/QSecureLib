#include "asymmetric.hpp"

#include <oqs/oqs.h>

bool AsymmetricCrypto::generateKeyPair(
    std::vector<unsigned char>& publicKey,
    std::vector<unsigned char>& secretKey)
{
    OQS_KEM* kem =
        OQS_KEM_new(OQS_KEM_alg_ml_kem_768);

    if(!kem)
        return false;

    publicKey.resize(kem->length_public_key);
    secretKey.resize(kem->length_secret_key);

    OQS_STATUS status =
        OQS_KEM_keypair(
            kem,
            publicKey.data(),
            secretKey.data()
        );

    OQS_KEM_free(kem);

    return status == OQS_SUCCESS;
}

bool AsymmetricCrypto::encapsulate(
    const std::vector<unsigned char>& publicKey,
    std::vector<unsigned char>& ciphertext,
    std::vector<unsigned char>& sharedSecret)
{
    OQS_KEM* kem =
        OQS_KEM_new(OQS_KEM_alg_ml_kem_768);

    if(!kem)
        return false;

    ciphertext.resize(
        kem->length_ciphertext
    );

    sharedSecret.resize(
        kem->length_shared_secret
    );

    OQS_STATUS status =
        OQS_KEM_encaps(
            kem,
            ciphertext.data(),
            sharedSecret.data(),
            publicKey.data()
        );

    OQS_KEM_free(kem);

    return status == OQS_SUCCESS;
}

bool AsymmetricCrypto::decapsulate(
    const std::vector<unsigned char>& secretKey,
    const std::vector<unsigned char>& ciphertext,
    std::vector<unsigned char>& sharedSecret)
{
    OQS_KEM* kem =
        OQS_KEM_new(OQS_KEM_alg_ml_kem_768);

    if(!kem)
        return false;

    sharedSecret.resize(
        kem->length_shared_secret
    );

    OQS_STATUS status =
        OQS_KEM_decaps(
            kem,
            sharedSecret.data(),
            ciphertext.data(),
            secretKey.data()
        );

    OQS_KEM_free(kem);

    return status == OQS_SUCCESS;
}