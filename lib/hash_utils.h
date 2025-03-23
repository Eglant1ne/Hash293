#ifndef HASH_UTILS_H
#define HASH_UTILS_H

#include <vector>

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
 * @return The transformed integer.
 */
constexpr int whitening(int x) {
    return rotl((x ^ (x >> 3) ^ (x << 7)) * 0x45d9f3b, 13) ^ ((x >> 5) ^ (x << 11));
}

/**
 * @brief Fills a character vector with additional padding.
 *
 * This function appends `add` characters with a predefined pattern
 * to the end of `v`, ensuring the vector reaches the required length.
 *
 * @param v   The vector to be extended.
 * @param add The number of characters to add.
 */
void fill_vector(std::vector<char>& v, int add);

#endif // HASH_UTILS_H
