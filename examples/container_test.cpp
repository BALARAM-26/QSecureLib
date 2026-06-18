#include "container.hpp"

#include <iostream>

int main()
{
    std::vector<unsigned char>
        kemCiphertext =
        {1,2,3,4,5};

    std::vector<unsigned char>
        signature =
        {10,11,12,13,14,15};

    std::vector<unsigned char>
        encryptedData =
        {20,21,22,23,24,25,26};

    bool saved =
        Container::save(
            "sample.qsec",
            kemCiphertext,
            signature,
            encryptedData
        );

    if(!saved)
    {
        std::cout
            << "Save failed\n";

        return 1;
    }

    std::vector<unsigned char>
        loadedKem;

    std::vector<unsigned char>
        loadedSig;

    std::vector<unsigned char>
        loadedData;

    bool loaded =
        Container::load(
            "sample.qsec",
            loadedKem,
            loadedSig,
            loadedData
        );

    if(!loaded)
    {
        std::cout
            << "Load failed\n";

        return 1;
    }

    std::cout
        << "KEM size: "
        << loadedKem.size()
        << std::endl;

    std::cout
        << "Signature size: "
        << loadedSig.size()
        << std::endl;

    std::cout
        << "Data size: "
        << loadedData.size()
        << std::endl;

    std::cout
        << "Container test passed"
        << std::endl;

    return 0;
}