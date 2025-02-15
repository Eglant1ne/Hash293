#include "hash_utils.h"
#include "whitening.h"

/**
 * @details
 * This function reserves additional capacity in the vector
 * to minimize re-allocations, then uses `whitening` to generate
 * pseudo-random filler bytes.
 */
void fill_vector(std::vector<char>& v, int add, int salt) {
    v.reserve(v.size() + add);
    for (int i = 0; i < add; ++i) {
        char filler = static_cast<char>(whitening(salt + i) & 0xFF);
        v.push_back(filler);
    }
}
