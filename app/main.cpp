#include <iostream>
#include <vector>
#include "Hash293.h"

/**
 * @brief Entry point for the Hash293App application.
 */
int main() {
    std::string data = "Hello, world!";
    std::vector<char> input(data.begin(), data.end());

    std::string hashValue = Hash293::hash293(input);

    std::cout << "Hash result (hex): ";
    for (unsigned char c : hashValue) {
        std::cout << std::hex << static_cast<int>(c);
    }
    std::cout << std::endl;

    return 0;
}
