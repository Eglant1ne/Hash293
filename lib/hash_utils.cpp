#include "hash_utils.h"


char* fill_array(const char* data, int dataSize, int add, int block) {
    char* newData = new char[dataSize + add];
    std::memcpy(newData, data, dataSize);

    for (int i = 0; i < add; ++i) {
        newData[dataSize + i] = static_cast<char>(whitening(block + i, i));
    }

    return newData;
}

