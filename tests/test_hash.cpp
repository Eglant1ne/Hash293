#include <gtest/gtest.h>
#include "Hash293.h"
#include <string>
#include <random>
#include <unordered_set>
#include <vector>
#include <cstring>

/**
 * @test Basic check that hash293 returns a non-empty hash for a small input.
 */
TEST(Hash293Test, BasicHash) {
    const char* input = "Hello";
    int inputSize = strlen(input);

    char* hashResult = Hash293::hash293(input, inputSize);
    EXPECT_NE(hashResult, nullptr);

    delete[] hashResult;
}

/**
 * @test Verifies that the hash function does not crash on empty input.
 */
TEST(Hash293Test, EmptyInput) {
    const char* input = "";
    int inputSize = strlen(input);

    char* hashResult = Hash293::hash293(input, inputSize);
    EXPECT_NE(hashResult, nullptr); // Проверяем, что хэш не пустой

    delete[] hashResult; // Освобождаем память
}

/**
 * @test Checks that the same input yields the same hash on repeated calls.
 */
TEST(Hash293Test, SameInputProducesSameHash) {
    const char* input = "Same input";
    int inputSize = strlen(input);

    char* hashResult1 = Hash293::hash293(input, inputSize);
    char* hashResult2 = Hash293::hash293(input, inputSize);

    std::string hash1 = Hash293::toString(hashResult1);
    std::string hash2 = Hash293::toString(hashResult2);

    EXPECT_EQ(hash1, hash2);

    delete[] hashResult1;
    delete[] hashResult2;
}

/**
 * @test Verifies that two slightly different inputs likely produce different hashes.
 */
TEST(Hash293Test, DifferentInputProducesDifferentHash) {
    const char* input1 = "Hello world";
    const char* input2 = "Hello worle";
    int inputSize1 = strlen(input1);
    int inputSize2 = strlen(input2);

    char* hashResult1 = Hash293::hash293(input1, inputSize1);
    char* hashResult2 = Hash293::hash293(input2, inputSize2);

    std::string hash1 = Hash293::toString(hashResult1);
    std::string hash2 = Hash293::toString(hashResult2);

    EXPECT_NE(hash1, hash2);

    delete[] hashResult1;
    delete[] hashResult2;
}

/**
 * @test Large input test (1 million characters) to ensure no exceptions are thrown.
 */
TEST(Hash293Test, LargeInput) {
    const int largeSize = 1'000'000;
    char* bigData = new char[largeSize];
    std::memset(bigData, 'A', largeSize);

    char* hashResult = Hash293::hash293(bigData, largeSize);
    std::string hashString;

    ASSERT_NO_THROW(hashString = Hash293::toString(hashResult));
    EXPECT_FALSE(hashString.empty());

    delete[] bigData;
    delete[] hashResult;
}

/**
 * @test Generates random data to check for basic functionality.
 */
TEST(Hash293Test, RandomData) {
    const int randomSize = 1024;
    char* randomData = new char[randomSize];

    std::mt19937_64 rng(12345);
    std::uniform_int_distribution<int> dist(0, 255);

    for (int i = 0; i < randomSize; ++i) {
        randomData[i] = static_cast<char>(dist(rng));
    }

    char* hashResult = Hash293::hash293(randomData, randomSize);
    EXPECT_NE(hashResult, nullptr);

    delete[] randomData;
    delete[] hashResult;
}

TEST(Hash293Test, CollisionTestForOneMillionStrings) {
    const int numTests = 1'000'000;
    std::unordered_set<std::string> hashes;
    hashes.reserve(numTests);

    std::mt19937_64 rng(12345);
    std::uniform_int_distribution<char> dist('a', 'z');

    for (int i = 0; i < numTests; ++i) {
        std::string input(10, ' ');
        for (char& c : input) {
            c = dist(rng);
        }

        char* hashResult = Hash293::hash293(input.c_str(), input.size());
        std::string hashStr = Hash293::toString(hashResult);
        delete[] hashResult;

        ASSERT_EQ(hashes.find(hashStr), hashes.end())
            << "Collision detected for input: " << input;

        hashes.insert(hashStr);
    }

    EXPECT_EQ(hashes.size(), numTests);
}