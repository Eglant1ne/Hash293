#ifndef HASH293_H
#define HASH293_H

#include <string>
#include "hash_utils.h"
#include <cstdint>
#include <iomanip>
#include <sstream>
#include <utility>

/**
 * @class Hash293
 * @brief Implements a custom hashing algorithm with a fast and secure (Key-Stretching) variant.
 */
class Hash293 {
    public:
        /**
         * @brief Computes the hash of the input data (fast version).
         * @param data Input data.
         * @param dataSize Size of the input data.
         * @return Pointer to a dynamically allocated hash array (caller must free it).
         */
        static char* hash293(const char* data, uint32_t dataSize);
    
        /**
         * @brief Computes a more secure hash using Key-Stretching.
         * @param data Input data.
         * @param dataSize Size of the input data.
         * @param iterations Number of additional iterations for key strengthening.
         * @return Pointer to a dynamically allocated hash array (caller must free it).
         */
        static char* hash293_secure(const char* data, uint32_t dataSize, uint32_t iterations);
    
        /**
         * @brief Converts a hash array to a hex string representation.
         * @param hash Pointer to hash data.
         * @param hashSize Size of the hash.
         * @return Hexadecimal string representation of the hash.
         */
        static std::string to_hexdigit(const char* hash, uint32_t hashSize);

        /**
         * @brief Generates salt.
         * @
         */
    
    private:
        static char* fill_array(const char* data, int dataSize, int add, int block);
        static constexpr int rotl(int value, int shift);
        static constexpr int whitening(int x, int index);
    };
    
#endif