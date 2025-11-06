cmake_minimum_required(VERSION 3.16)
project(myownlab)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Основная программа
add_executable(myownlab
        main.cpp
        MyString.cpp
        MyString.h
        OctString.cpp
        OctString.h
        DataOctString.cpp
        DataOctString.h
        Tree.cpp
        Tree.h
)

# ==== GoogleTest ====
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# ==== Тесты ====
add_executable(run_tests
        tests/mystring_test.cpp
        tests/octstring_test.cpp
        tests/dataoctstring_test.cpp
        tests/tree_test.cpp
        MyString.cpp
        MyString.h
        OctString.cpp
        OctString.h
        DataOctString.cpp
        DataOctString.h
        Tree.cpp
        Tree.h

)

target_link_libraries(run_tests
        GTest::gtest_main
)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
        DOWNLOAD_EXTRACT_TIMESTAMP true
)

include(GoogleTest)
gtest_discover_tests(run_tests)
