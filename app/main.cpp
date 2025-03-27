#include <iostream>
#include "Hash293.h"

/**
 * @brief Entry point for the Hash293App application.
 * Example of use.
 */
int main() {
    const char* data = "ASDGWKGWEJGWGWJGWJGWEGHWGPIEWHGWHIGWIPIWIGHHIGWIGPIEWIHGHIGEWIHPGIWE";
    int dataSize = strlen(data);

    std::string hash_secure = Hash293::generate_hash293pw(data, dataSize, 4);
    std::string hash = Hash293::generate_hash293pw(data, dataSize);
    for(auto c: hash_secure) std::cout << c;
    
    std::cout << std::endl << hash_secure.size() << std::endl;

    std::cout << Hash293::verify_hash293pw(hash_secure, data, dataSize) << std::endl;
    for(auto c: hash) std::cout << c;
    
    std::cout << std::endl << hash.size() << std::endl;
    std::cout << Hash293::verify_hash293pw(hash, data, dataSize) << std::endl;
    return 0;
}