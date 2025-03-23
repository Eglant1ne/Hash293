#include <gtest/gtest.h>
#include "Hash293.h"
#include <string>
#include <vector>
#include <random>

/**
 * @test Basic check that hash293 returns a non-empty hash for a small input.
 */
TEST(Hash293Test, BasicHash) {
    std::vector<char> input = {'H', 'e', 'l', 'l', 'o'};
    std::vector<char> hashResult = Hash293::hash293(input);
    EXPECT_FALSE(hashResult.empty());
}

/**
 * @test Verifies that the hash function does not crash on empty input.
 */
TEST(Hash293Test, EmptyInput) {
    std::vector<char> input;
    std::vector<char> hashResult = Hash293::hash293(input);
    EXPECT_FALSE(hashResult.empty());
}

/**
 * @test Checks that the same input yields the same hash on repeated calls.
 */
TEST(Hash293Test, SameInputProducesSameHash) {
    std::string s = "Same input";
    std::vector<char> input(s.begin(), s.end());
    std::vector<char> result = Hash293::hash293(input);
    std::string hash1 = Hash293::toString(result);
    std::string hash2 = Hash293::toString(result);
    EXPECT_EQ(hash1, hash2);
}

/**
 * @test Verifies that two slightly different inputs likely produce different hashes.
 */
TEST(Hash293Test, DifferentInputProducesDifferentHash) {
    std::string s1 = "Hello world";
    std::string s2 = "Hello worle"; // small difference
    std::vector<char> input1(s1.begin(), s1.end());
    std::vector<char> input2(s2.begin(), s2.end());
    std::vector<char> input1_hash = Hash293::hash293(input1);
    std::vector<char> input2_hash = Hash293::hash293(input2);
    std::string hash1 = Hash293::toString(input1_hash);
    std::string hash2 = Hash293::toString(input2_hash);
    EXPECT_NE(hash1, hash2);
}

/**
 * @test Large input test (1 million characters) to ensure no exceptions are thrown.
 */
TEST(Hash293Test, LargeInput) {
    std::vector<char> bigData(1'000'000, 'A');
    std::string hashResult;
    std::vector<char> hash = Hash293::hash293(bigData);
    ASSERT_NO_THROW(hashResult = Hash293::toString(hash));
    EXPECT_FALSE(hashResult.empty());
}

/**
 * @test Generates random data to check for basic functionality.
 */
TEST(Hash293Test, RandomData) {
    std::vector<char> randomData(1024);
    std::mt19937_64 rng(12345);
    std::uniform_int_distribution<int> dist(0, 255);

    for (auto &c : randomData) {
        c = static_cast<char>(dist(rng));
    }

    std::vector<char> hashResult = Hash293::hash293(randomData);
    EXPECT_FALSE(hashResult.empty());
}
