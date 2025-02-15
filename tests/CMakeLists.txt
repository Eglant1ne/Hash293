# tests/CMakeLists.txt

find_package(GTest REQUIRED)

add_executable(Hash293Tests
    test_main.cpp
    test_hash.cpp
)

target_link_libraries(Hash293Tests
    PRIVATE
        Hash293Lib
        GTest::GTest
        GTest::Main
)

target_include_directories(Hash293Tests
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../lib
)

add_test(NAME Hash293Tests COMMAND Hash293Tests)
