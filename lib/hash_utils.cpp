#include "hash_utils.h"



uint32_t random_int() {
    // Generate a random integer within a specific range (10 to 32)
    uint8_t r;
    randombytes(&r, 1);
    return 10 + (r % 23);
}


std::string to_hexdigit(const char* data, size_t hashSize) {
    // Convert the data to a hexadecimal string
    std::stringstream result;
    for (uint32_t i = 0; i < hashSize; ++i) {
        result << std::hex << std::setw(2) << std::setfill('0')
               << static_cast<int>(static_cast<unsigned char>(data[i]));
    }
    return result.str();
}