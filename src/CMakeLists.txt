cmake_minimum_required(VERSION 3.13)

include(FetchContent)
FetchContent_Declare(
        googletest
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

SET(CMAKE_C_COMPILER clang)
SET(CMAKE_CXX_COMPILER clang++)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_EXE_LINKER_FLAGS_INIT "-fuse-ld=lld")
set(CMAKE_MODULE_LINKER_FLAGS_INIT "-fuse-ld=lld")
set(CMAKE_SHARED_LINKER_FLAGS_INIT "-fuse-ld=lld")
set(CMAKE_C_FLAGS "-fuse-ld=lld")
set(CMAKE_CXX_FLAGS "-fuse-ld=lld")

add_subdirectory(mock)
add_subdirectory(orig)
add_subdirectory(util)

add_executable(UnitTestSample main.cpp)

target_include_directories(UnitTestSample PRIVATE
        ./
        ./mock
)

target_link_libraries(UnitTestSample PRIVATE
        mockLib
        gcov
        gtest
        gmock
        pthread
)