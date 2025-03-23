#include "Hash293.h"


std::string Hash293::toString(std::vector<char>& data) {
    std::stringstream result;

    for (unsigned char i : data) {
        result << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(i);
    }

    return result.str();
}


std::vector<char> Hash293::hash293(std::vector<char>& data) {
    int len = data.size();

    int minSize = 64;
    while (minSize < len) {
        minSize <<= 1;
    }

    int add = minSize - len;

    std::vector<char> v = std::move(data);
    fill_vector(v, add);

    std::vector<int> prev;
    prev.reserve(v.size());
    for (int i = 0; i < v.size(); ++i) {
        prev.emplace_back(whitening(v[i] + i));
    }

    while (prev.size() > 64) {
        std::vector<int> temp;
        temp.reserve(prev.size() / 2);
        for (int j = 0; j < prev.size(); j += 2) {
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
    for (int i = 0; i < prev.size(); ++i) {
        int mixed = whitening(prev[i] * i + 1);
        hashArr.emplace_back(static_cast<char>(mixed));
    }

    for (int i = 0; i < hashArr.size(); ++i) {
        int tmp = static_cast<unsigned char>(hashArr[i]);
        hashArr[i] = static_cast<char>(whitening(tmp + i));
    }

    return hashArr;
}
