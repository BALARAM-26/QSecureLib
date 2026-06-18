#include "filehandler.hpp"

#include <fstream>
#include <iostream>

std::vector<unsigned char>
FileHandler::readFile(
    const std::string& filename)
{
    std::ifstream file(
        filename,
        std::ios::binary
    );

    if(!file.is_open())
    {
        std::cout
            << "Cannot open file: "
            << filename
            << std::endl;

        return {};
    }

    return std::vector<unsigned char>(
        std::istreambuf_iterator<char>(file),
        std::istreambuf_iterator<char>()
    );
}

bool FileHandler::writeFile(
    const std::string& filename,
    const std::vector<unsigned char>& data)
{
    std::ofstream file(
        filename,
        std::ios::binary
    );

    if(!file.is_open())
    {
        std::cout
            << "Cannot create file: "
            << filename
            << std::endl;

        return false;
    }

    file.write(
        reinterpret_cast<const char*>(
            data.data()
        ),
        data.size()
    );

    std::cout
        << "Wrote "
        << data.size()
        << " bytes to "
        << filename
        << std::endl;

    return file.good();
}