#include <iostream>
#include <vector>
#include "Hash293.h"

/**
 * @brief Entry point for the Hash293App application.
 */
int main() {
    std::string data = "something";
    std::vector<char> input(data.begin(), data.end());

    std::string hashValue = Hash293::hash293(input);

    std::cout << "Hash result (hex): ";
    for (auto c : hashValue) {
        std::cout << c;
    }
    std::cout << std::endl;

    return 0;
}
