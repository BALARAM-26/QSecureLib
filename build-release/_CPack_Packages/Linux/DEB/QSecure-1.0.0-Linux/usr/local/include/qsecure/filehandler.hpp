#ifndef FILEHANDLER_HPP
#define FILEHANDLER_HPP

#include <vector>
#include <string>

class FileHandler
{
public:

    // Read entire file into memory
    static std::vector<unsigned char>
    readFile(
        const std::string& filename
    );

    // Write binary data to file
    static bool
    writeFile(
        const std::string& filename,
        const std::vector<unsigned char>& data
    );
};

#endif
