#include <iostream>
#include <vector>
#include "Hash293.h"

/**
 * @brief Entry point for the Hash293App application.
 */
int main() {
    const char* data = "something";
    int dataSize = strlen(data);

    char* hash = Hash293::hash293(data, dataSize);

    std::string hashValue = Hash293::to_hexdigit(hash, 32); 

    std::cout << "Hash result (hex): ";
    for (char c : hashValue) {
        std::cout << c;
    }
    std::cout << std::endl;

    std::cout << "Hash value size: " << hashValue.size() << std::endl;

    delete[] hash;

    return 0;
}