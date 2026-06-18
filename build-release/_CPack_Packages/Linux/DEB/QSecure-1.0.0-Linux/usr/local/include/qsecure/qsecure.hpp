#ifndef QSECURE_HPP
#define QSECURE_HPP

#include <string>

class QSecure
{
public:

    bool encryptFile(
        const std::string& input,
        const std::string& output,
        const std::string& key
    );

    bool decryptFile(
        const std::string& input,
        const std::string& output,
        const std::string& key
    );
};

#endif
