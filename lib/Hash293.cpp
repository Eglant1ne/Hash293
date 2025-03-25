#include "Hash293.h"


constexpr int HASH_SIZE = 32;

char* Hash293::hash293(const char* data, uint32_t dataSize) {
    int len = dataSize;
    int minSize = HASH_SIZE;
    while (minSize < len) {
        minSize <<= 1;
    }

    int add = minSize - len;
    int block = 0;
    for (int i = 0; i < len; ++i) {
        block += data[i];
    }

    char* paddedData = fill_array(data, len, add, block);
    int paddedSize = len + add;

    int* prev = new int[paddedSize];
    for (int i = 0; i < paddedSize; ++i) {
        prev[i] = whitening((paddedData[i] * 31) ^ (i * 17) ^ (i << 3) + block, i);
    }
    delete[] paddedData;

    int prevSize = paddedSize;
    while (prevSize > HASH_SIZE) {
        int newSize = prevSize / 2;
        int* temp = new int[newSize];

        for (int j = 0; j < prevSize; j += 2) {
            int mixed = (prev[j] * 37) ^ (prev[j + 1] * 19) ^ (j * 13);
            temp[j / 2] = whitening(mixed, j);
        }

        delete[] prev;
        prev = temp;
        prevSize = newSize;
    }

    char* hashArr = new char[HASH_SIZE];
    for (int i = 0; i < HASH_SIZE; ++i) {
        int mixed = whitening((prev[i] * 41) ^ (i * 29) ^ (i << 5), i);
        hashArr[i] = static_cast<char>(mixed);
    }

    delete[] prev;

    for (int i = 0; i < HASH_SIZE; ++i) {
        int tmp = static_cast<unsigned char>(hashArr[i]);
        hashArr[i] = static_cast<char>(whitening(tmp + i, i));
    }

    return hashArr;
}

char* Hash293::hash293_secure(const char* data, uint32_t dataSize, uint32_t iterations) {
    char* hash = hash293(data, dataSize);

    for (uint32_t i = 0; i < iterations; ++i) {
        char* tempHash = hash293(hash, HASH_SIZE);
        delete[] hash;
        hash = tempHash;
    }

    return hash;
}

std::string Hash293::toString(const char* hash, uint32_t hashSize) {
    std::stringstream result;
    for (uint32_t i = 0; i < hashSize; ++i) {
        result << std::hex << std::setw(2) << std::setfill('0')
               << static_cast<int>(static_cast<unsigned char>(hash[i]));
    }
    return result.str();
}

char* Hash293::fill_array(const char* data, int dataSize, int add, int block) {
    char* newData = new char[dataSize + add];
    std::memcpy(newData, data, dataSize);

    for (int i = 0; i < add; ++i) {
        newData[dataSize + i] = static_cast<char>(whitening(block + i, i));
    }

    return newData;
}

constexpr int Hash293::rotl(int value, int shift) {
    return (value << shift) | (value >> (32 - shift));
}

constexpr int Hash293::whitening(int x, int index) {
    constexpr int prime = 0x45d9f3b;
    x ^= (x >> 16);
    x *= prime;
    x ^= (x >> 16);
    return rotl(x + (index * 31), index % 8);
}
