#include "hash_utils.h"


std::string to_hexdigit(const char* data, size_t hashSize) {
    // Convert the data to a hexadecimal string
    std::stringstream result;
    for (uint32_t i = 0; i < hashSize; ++i) {
        result << std::hex << std::setw(2) << std::setfill('0')
               << static_cast<int>(static_cast<unsigned char>(data[i]));
    }
    return result.str();
}

std::string generate_salt_string() {
    auto salt = Hash293::generate_salt();
    return to_hexdigit(salt.get(), 16);
}