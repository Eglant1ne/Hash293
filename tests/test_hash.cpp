#include <gtest/gtest.h>
#include "Hash293.h"
#include <string>
#include <random>
#include <unordered_set>
#include <sqlite3.h>
#include <memory>
#include <fstream>
#include <cstring>


/**
 * @class SQLiteBatchWrapper
 * @brief A wrapper class for SQLite database operations with batch processing support
 * 
 * This class provides optimized database operations with batch inserts and transaction management
 * for high-performance hash collision detection.
 */
class SQLiteBatchWrapper {
    public:
        /**
         * @brief Constructs a new SQLiteBatchWrapper instance
         * 
         * @param db_name Path to the SQLite database file
         * @throws std::runtime_error If database cannot be opened or initialized
         */
        SQLiteBatchWrapper(const std::string& db_name) : db_(nullptr) {
            if (sqlite3_open(db_name.c_str(), &db_) != SQLITE_OK) {
                throw std::runtime_error("Can't open database");
            }
            
            const char* create_table_sql = 
                "CREATE TABLE IF NOT EXISTS hashes ("
                "hash TEXT PRIMARY KEY,"
                "input TEXT);";
                
            execute_sql(create_table_sql);
            
            const char* insert_sql = "INSERT OR IGNORE INTO hashes (hash, input) VALUES (?, ?);";
            if (sqlite3_prepare_v2(db_, insert_sql, -1, &insert_stmt_, nullptr) != SQLITE_OK) {
                throw std::runtime_error("Can't prepare insert statement");
            }
            
            execute_sql("PRAGMA journal_mode=WAL;");
            execute_sql("PRAGMA synchronous=NORMAL;");
            execute_sql("PRAGMA cache_size=-10000;");
        }
        
        /**
         * @brief Destructor - ensures proper cleanup of database resources
         */
        ~SQLiteBatchWrapper() {
            flush_batch();
            sqlite3_finalize(insert_stmt_);
            sqlite3_close(db_);
        }
        /**
         * @brief Adds a hash-input pair to the current batch
         * 
         * @param hash The calculated hash value
         * @param input The original input string
         * @throws std::runtime_error If insert operation fails
         */
        void add_to_batch(const std::string& hash, const std::string& input) {
            sqlite3_reset(insert_stmt_);
            sqlite3_bind_text(insert_stmt_, 1, hash.c_str(), -1, SQLITE_TRANSIENT);
            sqlite3_bind_text(insert_stmt_, 2, input.c_str(), -1, SQLITE_TRANSIENT);
            
            if (sqlite3_step(insert_stmt_) != SQLITE_DONE) {
                throw std::runtime_error("Insert failed");
            }
            
            batch_count_++;
            if (batch_count_ >= batch_size_) {
                flush_batch();
            }
        }
        /**
         * @brief Finds a collision for the given hash value
         * 
         * @param hash The hash value to search for
         * @return std::string The original input that produced this hash, or empty string if not found
         */
        std::string find_collision(const std::string& hash) {
            sqlite3_stmt* stmt;
            const char* sql = "SELECT input FROM hashes WHERE hash = ? LIMIT 1;";
            
            if (sqlite3_prepare_v2(db_, sql, -1, &stmt, nullptr) != SQLITE_OK) {
                return "";
            }
            
            sqlite3_bind_text(stmt, 1, hash.c_str(), -1, SQLITE_TRANSIENT);
            
            std::string result;
            if (sqlite3_step(stmt) == SQLITE_ROW) {
                result = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            }
            
            sqlite3_finalize(stmt);
            return result;
        }
        
        /**
         * @brief Executes a raw SQL statement
         * 
         * @param sql The SQL statement to execute
         * @throws std::runtime_error If SQL execution fails
         */
        void execute_sql(const char* sql) {
            char* err_msg = nullptr;
            if (sqlite3_exec(db_, sql, nullptr, nullptr, &err_msg) != SQLITE_OK) {
                std::string error = err_msg ? err_msg : "Unknown error";
                sqlite3_free(err_msg);
                throw std::runtime_error("SQL error: " + error);
            }
        }
    
    private:
        /**
         * @brief Flushes the current batch to the database
         */
        void flush_batch() {
            if (batch_count_ > 0) {
                execute_sql("COMMIT; BEGIN TRANSACTION;");
                batch_count_ = 0;
            }
        }
        
        sqlite3* db_;
        sqlite3_stmt* insert_stmt_;
        int batch_count_ = 0;
        const int batch_size_ = 10000;
    };
    
    /**
     * @brief Test case for hash collision detection with SQLite batch processing
     * 
     * This test generates random input strings, computes their hashes, and checks for collisions
     * using SQLite database for storage with optimized batch operations.
     */
    TEST(Hash293Test, CollisionTestWithSQLiteBatch) {
        const long int numTests = 1'000'000;
        std::ofstream collisionLog("collisions.log");
        SQLiteBatchWrapper db("hashes.db");
    
        db.execute_sql("BEGIN TRANSACTION;");
    
        std::mt19937_64 rng(12345);
        std::uniform_int_distribution<char> dist('a', 'z');
    
        for (long int i = 0; i < numTests; ++i) {
            std::string input(10, ' ');
            for (char& c : input) {
                c = dist(rng);
            }
    
            char* hashResult = Hash293::hash293(input.c_str(), input.size());
            std::string hashStr = Hash293::to_hexdigit(hashResult, 32);
            delete[] hashResult;
    
            std::string existing_input = db.find_collision(hashStr);
            if (!existing_input.empty() && existing_input != input) {
                collisionLog << "Collision detected:\n"
                            << "  Input 1: " << existing_input << "\n"
                            << "  Input 2: " << input << "\n"
                            << "  Hash: " << hashStr << "\n\n";
            } else {
                db.add_to_batch(hashStr, input);
            }
    
            if (i % 100'000 == 0) {
                std::cout << "Processed " << i << " strings..." << std::endl;
            }
        }
    
        db.execute_sql("COMMIT;");
    }

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
    EXPECT_NE(hashResult, nullptr);

    delete[] hashResult;
}

/**
 * @test Checks that the same input yields the same hash on repeated calls.
 */
TEST(Hash293Test, SameInputProducesSameHash) {
    const char* input = "Same input";
    int inputSize = strlen(input);

    char* hashResult1 = Hash293::hash293(input, inputSize);
    char* hashResult2 = Hash293::hash293(input, inputSize);

    std::string hash1 = Hash293::to_hexdigit(hashResult1, 32);
    std::string hash2 = Hash293::to_hexdigit(hashResult2, 32);

    EXPECT_EQ(hash1, hash2);

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

    ASSERT_NO_THROW(hashString = Hash293::to_hexdigit(hashResult, 32));
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

