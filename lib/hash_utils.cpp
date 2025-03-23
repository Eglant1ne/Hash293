#include "hash_utils.h"

/**
 * @brief Fills a character vector with additional padding.
 *
 * This function appends `add` characters with a predefined pattern
 * to the end of `v`, ensuring the vector reaches the required length.
 *
 * @param v   The vector to be extended.
 * @param add The number of characters to add.
 */
void fill_vector(std::vector<char>& v, int add) {
    for (int i = 0; i < add; ++i) {
        v.push_back(static_cast<char>(i % 256));  // Example padding pattern
    }
}
