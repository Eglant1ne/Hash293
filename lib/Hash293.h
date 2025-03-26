#ifndef HASH293_H
#define HASH293_H

#include <string>
#include "hash_utils.h"
#include <cstdint>
#include <iomanip>
#include <cmath>
#include <sstream>
#include <sodium.h>
#include <memory>
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
        static char* hash293(const char* data, size_t dataSize);
    
        /**
         * @brief Computes a more secure hash using Key-Stretching.
         * @param data Input data.
         * @param dataSize Size of the input data.
         * @param iterations Number of additional iterations for key strengthening.
         * @return Pointer to a dynamically allocated hash array (caller must free it).
         */
        static char* hash293_secure(const char* data, size_t dataSize, uint32_t iterations);
    
        /**
         * @brief Converts a hash array to a hex string representation.
         * @param hash Pointer to hash data.
         * @param hashSize Hash size.
         * @return Hexadecimal string representation of the hash.
         */
        static std::string to_hexdigit(const char* hash, size_t hashSize);

        /**
         * @brief Generates salt.
         * @return Random bytes array.
         */
         static std::unique_ptr<char[]> generate_salt();
    
    private:
        /**
         * @brief Pads the input data with additional bytes.
         * 
         * This function expands the input data to the required size by adding extra bytes,
         * which are derived from the `block` value and transformed using the whitening function.
         * 
         * @param data The original input data.
         * @param dataSize The size of the input data.
         * @param add The number of additional bytes to be appended.
         * @param block A computed value used to generate padding.
         * @return A new dynamically allocated array containing the padded data.
         */
        static char* fill_array(const char* data, size_t dataSize, int add, int block);

        /**
         * @brief Performs a left rotation on a 32-bit integer.
         * 
         * This function rotates the bits of `value` to the left by `shift` positions,
         * ensuring that overflowed bits wrap around to the right side.
         * 
         * @param value The integer value to be rotated.
         * @param shift The number of bits to rotate.
         * @return The rotated integer.
         */
        static constexpr uint32_t rotl(uint32_t value, uint32_t shift);

        /**
         * @brief Applies a whitening transformation to an integer.
         * 
         * This function performs a series of bitwise operations and multiplications to
         * introduce diffusion and improve randomness in the hashing process.
         * 
         * @param x The input integer to be whitened.
         * @param index The index used to further alter the transformation.
         * @return The transformed integer.
         */
        static constexpr uint32_t whitening(uint32_t x, uint32_t index);

        /**
         * @brief Generates a random integer within a specific range.
         * 
         * This function uses a cryptographic random number generator to produce a value
         * within the range [10, 32].
         * 
         * @return A random integer in the range [10, 32].
         */
        static uint32_t random_int();
    };
    
#endif