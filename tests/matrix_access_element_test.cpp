#include <gtest/gtest.h>

#include <iostream>

#include "../src/matrix.h"

// static_assert is a valid statement inside a TEST body, so this compile-time
// check gets a named entry in the gtest output instead of being invisible
// file-scope code. A violation still fails the build rather than the test run.
TEST(MatrixAccessElements, AtExposesConstCorrectElementReferences) {
    // A const Matrix only ever exposes read-only element access (const
    // double&), so its elements cannot be mutated through at().
    static_assert(std::is_same_v<decltype(std::declval<const Matrix&>().at(0, 0)), const double&>);
    static_assert(std::is_same_v<decltype(std::declval<Matrix&>().at(0, 0)), double&>);
}

TEST(MatrixAccessElements, AllowsUpdatingAnElement) {
    Matrix matrix(2, 2);

    std::cout << "Before setting element (1, 1):\n" << matrix << '\n';
    matrix.at(1, 1) = 42.5;
    std::cout << "After setting element (1, 1) to 42.5:\n" << matrix << '\n';

    EXPECT_DOUBLE_EQ(matrix.at(1, 1), 42.5);
}

TEST(MatrixAccessElements, ThrowsForOutOfRangeCoordinates) {
    Matrix matrix(2, 2);

    std::cout << "Reading coordinates outside this 2x2 matrix must throw std::out_of_range:\n"
              << matrix << '\n';
    EXPECT_THROW(matrix.at(2, 0), std::out_of_range);
    EXPECT_THROW(matrix.at(0, 2), std::out_of_range);
}
