#ifndef HASH_UTILS_H
#define HASH_UTILS_H

#include <cstring>
#include <cstdint>
#include "Hash293.h"
#include <sodium.h>
#include <iomanip>
#include <string>


/**
 * @brief Converts a hash array to a hex string representation.
 * @param hash Pointer to hash data.
 * @param hashSize Hash size.
 * @return Hexadecimal string representation of the hash.
 */
std::string to_hexdigit(const char* hash, size_t hashSize);

/**
 * @brief Converts salt to string.
 * @return Salt string.
 */
std::string generate_salt_string();

#endif
