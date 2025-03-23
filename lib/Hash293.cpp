#include "Hash293.h"


std::string Hash293::toString(const char* data) {
    std::stringstream result;

    for (int i = 0; i < 64; ++i) {
        result << std::hex << std::setw(2) << std::setfill('0') 
               << static_cast<int>(static_cast<unsigned char>(data[i]));
    }

    return result.str();
}

char* Hash293::hash293(const char* data, uint32_t dataSize) {
    int len = dataSize;

    int minSize = 64;
    while (minSize < len) {
        minSize <<= 1;
    }

    int add = minSize - len; // Number of padding bytes to add
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
    while (prevSize > 64) {
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

    char* hashArr = new char[prevSize];
    for (int i = 0; i < prevSize; ++i) {
        int mixed = whitening((prev[i] * 41) ^ (i * 29) ^ (i << 5), i);
        hashArr[i] = static_cast<char>(mixed);
    }

    delete[] prev;

    for (int i = 0; i < prevSize; ++i) {
        int tmp = static_cast<unsigned char>(hashArr[i]);
        hashArr[i] = static_cast<char>(whitening(tmp + i, i));
    }

    return hashArr;
}