#ifndef HASH_UTILS_H
#define HASH_UTILS_H

#include <cstring>


/**
 * @brief Performs a left rotate (circular shift left) on an integer.
 *
 * This function rotates the bits of `value` to the left by `shift` positions.
 * Bits shifted out from the left are wrapped around to the right.
 *
 * @param value The integer xvalue to rotate.
 * @param shift The number of bit positions to shift.
 * @return The result after applying the left rotation.
 */
constexpr int rotl(int value, int shift) {
    return (value << shift) | (value >> (32 - shift));
}

/**
 * @brief Applies a whitening transformation to an integer.
 *
 * This function performs a bitwise transformation using multiplication
 * with prime numbers and a left rotation to increase diffusion.
 *
 * @param x The input integer to transform.
 * @param index The index of x
 * @return The transformed integer.
 */
constexpr int whitening(int x, int index) {
    constexpr int prime = 0x45d9f3b;
    x ^= (x >> 16);  
    x *= prime;
    x ^= (x >> 16);
    return rotl(x + (index * 31), index % 8);
}


/**
 * @brief Fills a character array with additional padding.
 *
 * This function appends `add` characters with a predefined pattern
 * to the end of `data`, ensuring the array reaches the required length.
 *
 * @param v   The vector to be extended.
 * @param dataSize  The current size of the array.
 * @param add The number of characters to add.
 * @param block     A value used for padding calculation.
 * @return A new dynamically allocated array with the extended data.
 */
char* fill_array(const char* data, int dataSize, int add, int block);

#endif // HASH_UTILS_H
