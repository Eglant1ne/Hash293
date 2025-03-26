# lib/CMakeLists.txt

add_library(Hash293Lib STATIC
    Hash293.cpp
    hash_utils.cpp
)

target_link_libraries(Hash293Lib 
    PRIVATE 
    libsodium.dll
)

target_include_directories(Hash293Lib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
