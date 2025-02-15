#ifndef HASH_UTILS_H
#define HASH_UTILS_H

#include <vector>

/**
 * @brief Fills a character vector with additional data.
 *
 * This function appends `add` characters to the end of `v`,
 * using a salt-based strategy to add variability.
 *
 * @param v   The vector to be extended.
 * @param add The number of characters to add.
 * @param salt An integer value used to generate filler bytes.
 */
void fill_vector(std::vector<char>& v, int add, int salt);

#endif // HASH_UTILS_H
