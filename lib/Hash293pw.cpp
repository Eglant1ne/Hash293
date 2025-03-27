#include "Hash293.h"

std::string Hash293::generate_hash293pw(const char* data, size_t dataSize, uint32_t iterations, std::string salt) {
    if (salt.empty()) salt = generate_salt_string();
    
    std::string dataWithSalt = salt + std::string(data, dataSize);
    std::string algo;
    char* hash;

    if (iterations < 2) {
        hash = Hash293::hash293(dataWithSalt.c_str(), dataWithSalt.size());
        algo = "hash293d";
    } else {
        hash = Hash293::hash293_secure(dataWithSalt.c_str(), dataWithSalt.size(), iterations);
        algo = "hash293s";
    }

    std::string iter = std::to_string(iterations);
    std::string finalHash = algo + "#" + iter + "#" + salt + "#" + to_hexdigit(hash, HASH_SIZE);

    delete[] hash;
    return finalHash;
}


bool Hash293::verify_hash293pw(const std::string& stored, const char* input, size_t inputSize) {
    // Find separators in the stored string (algo#iterations#salt#hash)
    size_t pos1 = stored.find('#');
    if (pos1 == std::string::npos) return false;
    
    size_t pos2 = stored.find('#', pos1 + 1);
    if (pos2 == std::string::npos) return false;
    
    size_t pos3 = stored.find('#', pos2 + 1);
    if (pos3 == std::string::npos) return false;

    // Extract parts from the stored string
    std::string algo = stored.substr(0, pos1);
    uint32_t iterations = std::stoi(stored.substr(pos1 + 1, pos2 - pos1 - 1));
    std::string salt = stored.substr(pos2 + 1, pos3 - pos2 - 1);
    std::string expectedHash = stored.substr(pos3 + 1);

    // Combine the extracted salt with the input data
    std::string inputWithSalt = salt + std::string(input, inputSize);

    // Select the appropriate hashing algorithm (optimized with default case)
    char* hash = nullptr;
    
    if (algo == "hash293s") {
        hash = Hash293::hash293_secure(inputWithSalt.c_str(), inputWithSalt.size(), iterations);
    } else { 
        // Default case: if algo is invalid or unspecified, use hash293d
        hash = Hash293::hash293(inputWithSalt.c_str(), inputWithSalt.size());
    }

    // Convert the computed hash to a hexadecimal string
    std::string computedHash = to_hexdigit(hash, HASH_SIZE);
    delete[] hash;

    // Compare the computed hash with the stored hash using a loop
    bool sameHashes = true;
    for (size_t i = 0; i < 64; ++i) {
        if (computedHash[i] != expectedHash[i]) {
            sameHashes = false;
        }
    }

    return sameHashes;
}