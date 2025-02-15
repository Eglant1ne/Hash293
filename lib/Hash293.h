#ifndef HASH293_H
#define HASH293_H

#include <vector>
#include <string>

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
     * @return A std::string containing the resulting hash.
     */
    static std::string hash293(const std::vector<char>& data);
};

#endif // HASH293_H
