#include <iostream>
#include "Hash293.h"

/**
 * @brief Entry point for the Hash293App application.
 * Example of use.
 */
int main() {
    const char* data = "ASDGWKGWEJGWGWJGWJGWEGHWGPIEWHGWHIGWIPIWIGHHIGWIGPIEWIHGHIGEWIHPGIWE";
    int dataSize = strlen(data);

    std::string hash = Hash293::generate_hash293(data, dataSize, 4);
    std::cout << Hash293::verify_hash(hash, data, dataSize, 4);
    return 0;
}