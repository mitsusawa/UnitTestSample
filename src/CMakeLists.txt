cmake_minimum_required(VERSION 3.13)

include(FetchContent)

SET(CMAKE_C_COMPILER /usr/bin/clang)
SET(CMAKE_CXX_COMPILER /usr/bin/clang++)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_EXE_LINKER_FLAGS_INIT "-fuse-ld=lld")
set(CMAKE_MODULE_LINKER_FLAGS_INIT "-fuse-ld=lld")
set(CMAKE_SHARED_LINKER_FLAGS_INIT "-fuse-ld=lld")
set(CMAKE_C_FLAGS "-g0 -fcoverage-mapping -fprofile-instr-generate -fuse-ld=lld -fpermissive -lc++")
set(CMAKE_CXX_FLAGS "-g0 -fcoverage-mapping -fprofile-instr-generate -fuse-ld=lld -fpermissive -stdlib=libc++")

FetchContent_Declare(
        googletest
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_subdirectory(mock)
add_subdirectory(orig)
add_subdirectory(util)

add_executable(UnitTestSample main.cpp)

target_include_directories(UnitTestSample PRIVATE
        ./
        ./util
        ./mock
        ./orig
)

target_link_libraries(UnitTestSample PRIVATE
        mockLib
        OrigHogeLib
        OrigFugaLib

        gcov
        gtest
        gmock
        pthread
)
