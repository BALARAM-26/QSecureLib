#include "asymmetric.hpp"
#include "signature.hpp"

#include <chrono>
#include <iostream>

int main()
{
    using namespace std::chrono;

    std::vector<unsigned char> pubKey;
    std::vector<unsigned char> secKey;

    auto start =
        high_resolution_clock::now();

    AsymmetricCrypto::generateKeyPair(
        pubKey,
        secKey
    );

    auto end =
        high_resolution_clock::now();

    std::cout
        << "ML-KEM KeyGen: "
        << duration_cast<microseconds>(
               end - start
           ).count()
        << " us\n";

    std::vector<unsigned char>
        ciphertext,
        shared1,
        shared2;

    start =
        high_resolution_clock::now();

    AsymmetricCrypto::encapsulate(
        pubKey,
        ciphertext,
        shared1
    );

    end =
        high_resolution_clock::now();

    std::cout
        << "ML-KEM Encap: "
        << duration_cast<microseconds>(
               end - start
           ).count()
        << " us\n";

    start =
        high_resolution_clock::now();

    AsymmetricCrypto::decapsulate(
        secKey,
        ciphertext,
        shared2
    );

    end =
        high_resolution_clock::now();

    std::cout
        << "ML-KEM Decap: "
        << duration_cast<microseconds>(
               end - start
           ).count()
        << " us\n";

    std::vector<unsigned char>
        signPub,
        signPriv;

    start =
        high_resolution_clock::now();

    Signature::generateKeyPair(
        signPub,
        signPriv
    );

    end =
        high_resolution_clock::now();

    std::cout
        << "ML-DSA KeyGen: "
        << duration_cast<microseconds>(
               end - start
           ).count()
        << " us\n";

    std::vector<unsigned char>
        message =
        {'H','e','l','l','o'};

    std::vector<unsigned char>
        signature;

    start =
        high_resolution_clock::now();

    Signature::sign(
        message,
        signPriv,
        signature
    );

    end =
        high_resolution_clock::now();

    std::cout
        << "ML-DSA Sign: "
        << duration_cast<microseconds>(
               end - start
           ).count()
        << " us\n";

    start =
        high_resolution_clock::now();

    Signature::verify(
        message,
        signPub,
        signature
    );

    end =
        high_resolution_clock::now();

    std::cout
        << "ML-DSA Verify: "
        << duration_cast<microseconds>(
               end - start
           ).count()
        << " us\n";

    return 0;
}