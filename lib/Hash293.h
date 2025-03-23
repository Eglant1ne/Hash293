#ifndef HASH293_H
#define HASH293_H

#include <vector>
#include <string>
#include "hash_utils.h"
#include <iomanip>
#include <sstream>
#include <utility>

/**
 * @class Hash293
 * @brief A class providing the main hashing interface.
 *
 * The Hash293 class implements a custom hashing algorithm
 * using a combination of data padding, compression, and bit-mixing.
 */
class Hash293 {
public:
    /**
     * @brief Calculates a hash value for the given data.
     *
     * @param data A vector of characters representing the input data.
     * @return a vector of characters
     */
    static std::vector<char> hash293(std::vector<char>& data);
    /**
     * @brief Convert data to string.
     *
     * @param data A vector of characters.
     * @return data vector to string.
     */
    static std::string toString(std::vector<char>& data);
};

#endif // HASH293_H
