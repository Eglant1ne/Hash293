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
    int block = 0;
    for (char d: data) {
        block += d;
    }
    std::vector<char> v = std::move(data);
    fill_vector(v, add, block);

    std::vector<int> prev;
    prev.reserve(v.size());
    for (int i = 0; i < v.size(); ++i) {
        prev.emplace_back(whitening((v[i] * 31) ^ (i * 17) ^ (i << 3) + block, i));
    }

    while (prev.size() > 64) {
        std::vector<int> temp;
        temp.reserve(prev.size() / 2);
        for (int j = 0; j < prev.size(); j += 2) {
            int mixed = (prev[j] * 37) ^ (prev[j + 1] * 19) ^ (j * 13);
            temp.emplace_back(whitening(mixed, j));
        }
        prev = std::move(temp);
    }
    
    
    std::vector<char> hashArr;
    hashArr.reserve(prev.size());
    for (int i = 0; i < prev.size(); ++i) {
        int mixed = whitening((prev[i] * 41) ^ (i * 29) ^ (i << 5), i);
        hashArr.emplace_back(static_cast<char>(mixed));
    }    
    

    for (int i = 0; i < hashArr.size(); ++i) {
        int tmp = static_cast<unsigned char>(hashArr[i]);
        hashArr[i] = static_cast<char>(whitening(tmp + i, i));
    }

    return hashArr;
}
