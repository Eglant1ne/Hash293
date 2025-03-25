# tests/CMakeLists.txt

find_package(GTest REQUIRED)
find_package(SQLite3 REQUIRED)

add_executable(Hash293Tests
    test_main.cpp
    test_securehash.cpp
    test_hash.cpp
)

target_link_libraries(Hash293Tests
    PRIVATE
        Hash293Lib
        SQLite::SQLite3
        GTest::GTest
        GTest::Main
)

target_include_directories(Hash293Tests
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../lib
)

