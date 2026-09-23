cmake_minimum_required(VERSION 4.3)
set(CMAKE_CXX_STANDARD 23)

project(matrix_lib)

include(FetchContent)
include(CTest)

add_library(matrix_lib src/matrix.cpp
        src/utils/std_extensions.h
        src/matrix.h)
target_include_directories(matrix_lib PUBLIC src)

add_executable(matrix_example examples/main.cpp)
target_link_libraries(matrix_example PRIVATE matrix_lib)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(matrix_tests
        tests/matrix_construction_test.cpp
        tests/matrix_access_test.cpp
        tests/matrix_formatting_test.cpp
        tests/matrix_comparison_test.cpp
        tests/matrix_iterator_test.cpp
        tests/matrix_basic_arithmetic_operations.cpp
        tests/matrix_matrix_operations.cpp
        tests/matrix_linear_solver.cpp
)
target_link_libraries(matrix_tests PRIVATE matrix_lib GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(matrix_tests)