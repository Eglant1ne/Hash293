#include <iostream>
#include <vector>
#include "Hash293.h"

/**
 * @brief Entry point for the Hash293App application.
 */
int main() {
    std::string data = "samething";
    std::vector<char> input(data.begin(), data.end());

    std::vector hash = Hash293::hash293(input);
    std::string hashValue = Hash293::toString(hash);

    std::cout << "Hash result (hex): ";

    for (char c : hashValue) {
        std::cout << c;
    }

    std::cout << std::endl;
    std::cout << hashValue.size();
    return 0;
}
