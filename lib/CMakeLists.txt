# lib/CMakeLists.txt

add_library(Hash293Lib STATIC
    Hash293.cpp
    whitening.cpp
    hash_utils.cpp
)

target_include_directories(Hash293Lib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
