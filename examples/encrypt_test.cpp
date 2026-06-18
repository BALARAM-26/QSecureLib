#include "qsecure.hpp"

int main()
{
    QSecure crypto;

   crypto.encryptFile(
    "../sample.txt",
    "sample.enc",
    "secret123"
    );

    crypto.decryptFile(
        "sample.enc",
        "sample_copy.txt",
        "wrongpassword"
    );

    return 0;
}