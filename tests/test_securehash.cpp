#include <gtest/gtest.h>
#include <string>
#include <random>
#include "Hash293.h"
#include <unordered_set>
#include <sqlite3.h>
#include <memory>
#include <fstream>
#include <cstring>

constexpr int iter = 10000;

TEST(SecureHash293Test, BasicHash) {
    const char* input = "Hello";
    int inputSize = strlen(input);

    char* hashResult = Hash293::hash293_secure(input, inputSize, iter);
    EXPECT_NE(hashResult, nullptr);

    delete[] hashResult;
}

TEST(SecureHash293Test, EmptyInput) {
    const char* input = "";
    int inputSize = strlen(input);

    char* hashResult = Hash293::hash293_secure(input, inputSize, iter);
    EXPECT_NE(hashResult, nullptr);

    delete[] hashResult;
}

TEST(SecureHash293Test, SameInputProducesSameHash) {
    const char* input = "Same input";
    int inputSize = strlen(input);

    char* hashResult1 = Hash293::hash293_secure(input, inputSize, iter);
    char* hashResult2 = Hash293::hash293_secure(input, inputSize, iter);

    std::string hash1 = Hash293::toString(hashResult1, 32);
    std::string hash2 = Hash293::toString(hashResult2, 32);

    EXPECT_EQ(hash1, hash2);

    delete[] hashResult1;
    delete[] hashResult2;
}

TEST(SecureHash293Test, LargeInput) {
    const int largeSize = 1'000'000;
    char* bigData = new char[largeSize];
    std::memset(bigData, 'A', largeSize);

    char* hashResult = Hash293::hash293_secure(bigData, largeSize, iter);
    std::string hashString;

    ASSERT_NO_THROW(hashString = Hash293::toString(hashResult, 32));
    EXPECT_FALSE(hashString.empty());

    delete[] bigData;
    delete[] hashResult;
}

TEST(SecureHash293Test, RandomData) {
    const int randomSize = 1024;
    char* randomData = new char[randomSize];

    std::mt19937_64 rng(12345);
    std::uniform_int_distribution<int> dist(0, 255);

    for (int i = 0; i < randomSize; ++i) {
        randomData[i] = static_cast<char>(dist(rng));
    }

    char* hashResult = Hash293::hash293_secure(randomData, randomSize, iter);
    EXPECT_NE(hashResult, nullptr);

    delete[] randomData;
    delete[] hashResult;
}
