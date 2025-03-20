#include "Hash293.h"
#include "whitening.h"
#include "hash_utils.h"
#include <iomanip>
#include <sstream>
#include <utility>

std::string Hash293::hash293(const std::vector<char>& data) {
    int len = static_cast<int>(data.size());

    int minSize = 64;
    while (minSize < len) {
        minSize <<= 1;
    }
    if ((minSize - len) < 64) {
        minSize <<= 1;
    }

    int add = minSize - len;

    int salt = 0;
    for (char c : data) {
        salt += static_cast<unsigned char>(c);
    }
    salt = whitening(salt - len);

    std::vector<char> v = data;
    fill_vector(v, add, salt);

    std::vector<int> prev;
    prev.reserve(v.size());
    for (size_t i = 0; i < v.size(); ++i) {
        prev.emplace_back(whitening(v[i] + salt + static_cast<int>(i)));
    }

    while (prev.size() > 64) {
        std::vector<int> temp;
        temp.reserve(prev.size() / 2);
        for (size_t j = 0; j < prev.size(); j += 2) {
            if (j + 1 < prev.size()) {
                temp.emplace_back(whitening(prev[j] + prev[j + 1]));
            } else {
                temp.emplace_back(whitening(prev[j]));
            }
        }
        prev = std::move(temp);
    }

    std::vector<char> hashArr;
    hashArr.reserve(prev.size());
    for (size_t i = 0; i < prev.size(); ++i) {
        int mixed = whitening(prev[i] * static_cast<int>(i + 1));
        hashArr.emplace_back(static_cast<char>(mixed & 0xFF));
    }

    for (size_t i = 0; i < hashArr.size(); ++i) {
        int tmp = static_cast<unsigned char>(hashArr[i]);
        tmp = whitening(tmp + static_cast<int>(i));
        hashArr[i] = static_cast<char>(tmp & 0xFF);
    }
    std::stringstream result;

    for (unsigned char i : std::string(hashArr.begin(), hashArr.end())) {
        result << std::hex << static_cast<int>(i);
    }


    return result.str().substr(0, 64);
}
