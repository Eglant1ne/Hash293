#include "Hash293.h"

constexpr int HASH_SIZE = 32;


std::string Hash293::generate_hash293(const char* data, size_t dataSize, uint32_t iterations) {
    std::string salt = generate_salt_string();
    std::string dataWithSalt = salt + std::string(data, dataSize);

    char* hash = Hash293::hash293_secure(dataWithSalt.c_str(), dataWithSalt.size(), iterations);
    std::string finalHash = salt + "#" + to_hexdigit(hash, HASH_SIZE);

    delete[] hash;

    return finalHash;
}


bool Hash293::verify_hash(std::string stored, const char* input, size_t inputSize, uint32_t iterations) {
    // Find the separator between salt and hash in the stored string
    size_t pos = stored.find('#');
    if (pos == std::string::npos) return false;  // Invalid format if separator not found

    // Extract salt and expected hash from stored string
    std::string salt = stored.substr(0, pos);
    std::string expectedHash = stored.substr(pos + 1);

    // Combine the extracted salt with the input data
    std::string inputWithSalt = salt + std::string(input, inputSize);
    
    // Generate hash for verification using same parameters
    char* hash = hash293_secure(inputWithSalt.c_str(), inputWithSalt.size(), iterations);
    std::string computedHash = to_hexdigit(hash, HASH_SIZE);
    delete[] hash;  // Clean up dynamic allocation

    // Compare the computed hash with the stored expected hash
    bool sameHashes = true;
    for(uint32_t i = 0; i < 64; ++i) {
        if (computedHash[i] != expectedHash[i]) sameHashes = false;
    }
    return sameHashes;
}


char* Hash293::hash293(const char* data, size_t dataSize) {
    // Initialize variables
    int len = dataSize;
    int minSize = HASH_SIZE;

    // Determine the minimum power of 2 that is greater than or equal to len
    while (minSize < len) {
        minSize <<= 1;
    }

    // Calculate padding size
    int add = minSize - len;

    // Compute block sum (used for padding transformation)
    int block = 0;
    for (uint32_t i = 0; i < len; ++i) {
        block += data[i];
    }

    // Create padded data with additional bytes
    char* paddedData = fill_array(data, len, add, block);
    int paddedSize = len + add;

    // Initial transformation using whitening function
    int* prev = new int[paddedSize];
    for (uint32_t i = 0; i < paddedSize; ++i) {
        prev[i] = whitening((paddedData[i] * 31) ^ (i * 17) ^ (i << 3) + block, i);
    }
    delete[] paddedData; // Free memory after transformation

    // Reduce data size iteratively until it matches HASH_SIZE
    int prevSize = paddedSize;
    while (prevSize > HASH_SIZE) {
        int newSize = prevSize / 2;
        int* temp = new int[newSize];

        for (uint32_t j = 0; j < prevSize; j += 2) {
            int mixed = (prev[j] * 37) ^ (prev[j + 1] * 19) ^ (j * 13);
            temp[j / 2] = whitening(mixed, j);
        }

        delete[] prev; // Free previous buffer
        prev = temp;
        prevSize = newSize;
    }

    // Convert integer hash to a byte array
    char* hashArr = new char[HASH_SIZE];
    for (uint32_t i = 0; i < HASH_SIZE; ++i) {
        int mixed = whitening((prev[i] * 41) ^ (i * 29) ^ (i << 5), i);
        hashArr[i] = static_cast<char>(mixed);
    }

    delete[] prev; // Free memory

    // Final whitening step for additional diffusion
    for (uint32_t i = 0; i < HASH_SIZE; ++i) {
        int tmp = static_cast<unsigned char>(hashArr[i]);
        hashArr[i] = static_cast<char>(whitening(tmp + i, i));
    }

    return hashArr;
}


char* Hash293::hash293_secure(const char* data, size_t dataSize, uint32_t iterations) {
    // Generate the initial hash
    char* hash = hash293(data, dataSize);

    // Apply key-stretching with multiple iterations
    iterations = pow(2, iterations);
    for (uint32_t i = 0; i < iterations; ++i) {
        char* tempHash = hash293(hash, HASH_SIZE);
        delete[] hash; // Free previous hash
        hash = tempHash;
    }

    return hash;
}


char* Hash293::fill_array(const char* data, size_t dataSize, uint32_t add, uint32_t block) {
    // Create a new array with padding
    char* newData = new char[dataSize + add];
    std::memcpy(newData, data, dataSize);

    // Fill padding bytes using whitening function
    for (int i = 0; i < add; ++i) {
        newData[dataSize + i] = static_cast<char>(whitening(block + i, i));
    }

    return newData;
}


constexpr uint32_t Hash293::rotl(uint32_t value, uint32_t shift) {
    // Perform a left rotation of bits
    return (value << shift) | (value >> (32 - shift));
}


constexpr uint32_t Hash293::whitening(uint32_t x, uint32_t index) {
    // Apply a mix function to increase diffusion
    constexpr int prime = 0x45d9f3b;
    x ^= (x >> 16);
    x *= prime;
    x ^= (x >> 16);
    return rotl(x + (index * 31), index % 8);
}


std::unique_ptr<char[]> Hash293::generate_salt() {
    // Generate a random salt.
    uint32_t length = 16;
    auto buffer = std::make_unique<char[]>(length);
    randombytes_buf(buffer.get(), length);
    
    return buffer;
}
