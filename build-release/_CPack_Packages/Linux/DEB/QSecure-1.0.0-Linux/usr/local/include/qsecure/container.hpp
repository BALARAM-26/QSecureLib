#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <cstdint>

struct QSecHeader
{
    char magic[8];

    uint32_t version;

    uint32_t kemSize;
    uint32_t signatureSize;

    uint64_t encryptedDataSize;
};

#endif