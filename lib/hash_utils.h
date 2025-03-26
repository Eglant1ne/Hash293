#ifndef HASH_UTILS_H
#define HASH_UTILS_H

#include <cstring>
#include <cstdint>
#include "Hash293.h"
#include <sodium.h>
#include <iomanip>
#include <string>

/**
 * @brief Generates a random integer within a specific range.
 * 
 * This function uses a cryptographic random number generator to produce a value
 * within the range [10, 32].
 * 
 * @return A random integer in the range [10, 32].
 */
uint32_t random_int();

/**
 * @brief Converts a hash array to a hex string representation.
 * @param hash Pointer to hash data.
 * @param hashSize Hash size.
 * @return Hexadecimal string representation of the hash.
 */
std::string to_hexdigit(const char* hash, size_t hashSize);


std::string generate_salt_string();

#endif
