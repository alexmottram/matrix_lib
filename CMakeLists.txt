cmake_minimum_required(VERSION 4.3)
set(CMAKE_CXX_STANDARD 23)

project(matrix_lib)

include(FetchContent)
include(CTest)

add_library(matrix_lib src/matrix/matrix.cpp
        src/matrix/matrix_iterator.cpp
        src/matrix/matrix_slice_views.cpp
        src/utils/external_deps.h
        src/utils/std_extensions.h
        src/matrix/matrix.h
        src/matrix/matrix_lib.h
        src/matrix/matrix_iterator.h
        src/matrix/matrix_slice_iterators.h
        src/matrix/matrix_slice_views.h)
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
        tests/matrix/matrix_construction_test.cpp
        tests/matrix/matrix_access_element_test.cpp
        tests/matrix/matrix_formatting_test.cpp
        tests/matrix/matrix_comparison_test.cpp
        tests/matrix/matrix_iterator_test.cpp
        tests/matrix/matrix_row_column_test.cpp
        tests/matrix/matrix_basic_arithmetic_operations.cpp
        tests/matrix/matrix_matrix_operations.cpp
        tests/matrix/matrix_iterator_row_col_test.cpp
)
target_link_libraries(matrix_tests PRIVATE matrix_lib GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(matrix_tests)