# app/CMakeLists.txt

add_executable(Hash293App
    main.cpp
)

target_link_libraries(Hash293App PRIVATE Hash293Lib)

target_include_directories(Hash293App
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../lib
)
