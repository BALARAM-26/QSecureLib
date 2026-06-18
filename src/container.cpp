#include "container.hpp"

#include <fstream>
#include <cstdint>

bool Container::save(
    const std::string& filename,
    const std::vector<unsigned char>& kemCiphertext,
    const std::vector<unsigned char>& signature,
    const std::vector<unsigned char>& encryptedData)
{
    std::ofstream file(
        filename,
        std::ios::binary
    );

    if(!file)
        return false;

    uint32_t kemSize =
        static_cast<uint32_t>(
            kemCiphertext.size()
        );

    uint32_t sigSize =
        static_cast<uint32_t>(
            signature.size()
        );

    uint32_t dataSize =
        static_cast<uint32_t>(
            encryptedData.size()
        );

    file.write("QSEC", 4);

    file.write(
        reinterpret_cast<char*>(&kemSize),
        sizeof(kemSize)
    );

    file.write(
        reinterpret_cast<char*>(&sigSize),
        sizeof(sigSize)
    );

    file.write(
        reinterpret_cast<char*>(&dataSize),
        sizeof(dataSize)
    );

    file.write(
        reinterpret_cast<const char*>(
            kemCiphertext.data()
        ),
        kemSize
    );

    file.write(
        reinterpret_cast<const char*>(
            signature.data()
        ),
        sigSize
    );

    file.write(
        reinterpret_cast<const char*>(
            encryptedData.data()
        ),
        dataSize
    );

    return true;
}

bool Container::load(
    const std::string& filename,
    std::vector<unsigned char>& kemCiphertext,
    std::vector<unsigned char>& signature,
    std::vector<unsigned char>& encryptedData)
{
    std::ifstream file(
        filename,
        std::ios::binary
    );

    if(!file)
        return false;

    char magic[4];

    file.read(
        magic,
        4
    );

    if(
        magic[0] != 'Q' ||
        magic[1] != 'S' ||
        magic[2] != 'E' ||
        magic[3] != 'C'
    )
    {
        return false;
    }

    uint32_t kemSize;
    uint32_t sigSize;
    uint32_t dataSize;

    file.read(
        reinterpret_cast<char*>(&kemSize),
        sizeof(kemSize)
    );

    file.read(
        reinterpret_cast<char*>(&sigSize),
        sizeof(sigSize)
    );

    file.read(
        reinterpret_cast<char*>(&dataSize),
        sizeof(dataSize)
    );

    kemCiphertext.resize(
        kemSize
    );

    signature.resize(
        sigSize
    );

    encryptedData.resize(
        dataSize
    );

    file.read(
        reinterpret_cast<char*>(
            kemCiphertext.data()
        ),
        kemSize
    );

    file.read(
        reinterpret_cast<char*>(
            signature.data()
        ),
        sigSize
    );

    file.read(
        reinterpret_cast<char*>(
            encryptedData.data()
        ),
        dataSize
    );

    return true;
}