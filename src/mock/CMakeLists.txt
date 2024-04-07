cmake_minimum_required(VERSION 3.13)

SET(CMAKE_C_COMPILER clang)
SET(CMAKE_CXX_COMPILER clang++)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_EXE_LINKER_FLAGS_INIT "-fuse-ld=lld")
set(CMAKE_MODULE_LINKER_FLAGS_INIT "-fuse-ld=lld")
set(CMAKE_SHARED_LINKER_FLAGS_INIT "-fuse-ld=lld")

add_library(mockLib HogeFugaMock.cpp HogeFugaMock.hpp)

target_include_directories(mockLib PRIVATE
        ./
        ../orig
)

target_link_libraries(mockLib PRIVATE
        gcov
        gtest
        gmock
)
