#include "filehandler.hpp"
#include <iostream>

int main()
{
    auto data = FileHandler::readFile("../sample.txt");

    std::cout << "Bytes read: "
              << data.size()
              << std::endl;

    FileHandler::writeFile(
        "copy.txt",
        data
    );

    std::cout
        << "File copied successfully"
        << std::endl;

    return 0;
}