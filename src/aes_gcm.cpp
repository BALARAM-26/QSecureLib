#include "aes_gcm.hpp"

#include <openssl/evp.h>
#include <openssl/rand.h>

#include <cstring>
#include <iostream>

std::vector<unsigned char>
AESGCM::encrypt(
    const std::vector<unsigned char>& plaintext,
    const std::vector<unsigned char>& key)
{
    std::vector<unsigned char> ciphertext;

    EVP_CIPHER_CTX* ctx =
        EVP_CIPHER_CTX_new();

    if(!ctx)
        return ciphertext;

    const unsigned char* aesKey =
    key.data();

    unsigned char iv[12];

    RAND_bytes(iv, sizeof(iv));

    ciphertext.resize(
        plaintext.size() + 28
    );

    std::memcpy(
        ciphertext.data(),
        iv,
        12
    );

    int len = 0;
    int totalLen = 0;

    EVP_EncryptInit_ex(
        ctx,
        EVP_aes_256_gcm(),
        nullptr,
        nullptr,
        nullptr
    );

    EVP_CIPHER_CTX_ctrl(
        ctx,
        EVP_CTRL_GCM_SET_IVLEN,
        sizeof(iv),
        nullptr
    );

    EVP_EncryptInit_ex(
        ctx,
        nullptr,
        nullptr,
        aesKey,
        iv
    );

    EVP_EncryptUpdate(
        ctx,
        ciphertext.data() + 12,
        &len,
        plaintext.data(),
        plaintext.size()
    );

    totalLen = len;

    EVP_EncryptFinal_ex(
        ctx,
        ciphertext.data() + 12 + len,
        &len
    );

    totalLen += len;

    unsigned char tag[16];

    EVP_CIPHER_CTX_ctrl(
        ctx,
        EVP_CTRL_GCM_GET_TAG,
        16,
        tag
    );

    std::memcpy(
        ciphertext.data() + 12 + totalLen,
        tag,
        16
    );

    ciphertext.resize(
        12 + totalLen + 16
    );

    EVP_CIPHER_CTX_free(ctx);

    return ciphertext;
}

std::vector<unsigned char>
AESGCM::decrypt(
    const std::vector<unsigned char>& ciphertext,
    const std::vector<unsigned char>& key)
{
    std::vector<unsigned char> plaintext;

    if(ciphertext.size() < 28)
        return plaintext;

    EVP_CIPHER_CTX* ctx =
        EVP_CIPHER_CTX_new();

    if(!ctx)
        return plaintext;

    const unsigned char* aesKey =
    key.data();

    const unsigned char* iv =
        ciphertext.data();

    const unsigned char* tag =
        ciphertext.data()
        + ciphertext.size()
        - 16;

    size_t encryptedSize =
        ciphertext.size()
        - 12
        - 16;

    plaintext.resize(
        encryptedSize
    );

    int len = 0;
    int totalLen = 0;

    EVP_DecryptInit_ex(
        ctx,
        EVP_aes_256_gcm(),
        nullptr,
        nullptr,
        nullptr
    );

    EVP_CIPHER_CTX_ctrl(
        ctx,
        EVP_CTRL_GCM_SET_IVLEN,
        12,
        nullptr
    );

    EVP_DecryptInit_ex(
        ctx,
        nullptr,
        nullptr,
        aesKey,
        iv
    );

    EVP_DecryptUpdate(
        ctx,
        plaintext.data(),
        &len,
        ciphertext.data() + 12,
        encryptedSize
    );

    totalLen = len;

    EVP_CIPHER_CTX_ctrl(
        ctx,
        EVP_CTRL_GCM_SET_TAG,
        16,
        (void*)tag
    );

    int ret =
        EVP_DecryptFinal_ex(
            ctx,
            plaintext.data() + len,
            &len
        );

    EVP_CIPHER_CTX_free(ctx);

    if(ret <= 0)
    {
        plaintext.clear();
        return plaintext;
    }

    totalLen += len;

    plaintext.resize(totalLen);

    return plaintext;
}
