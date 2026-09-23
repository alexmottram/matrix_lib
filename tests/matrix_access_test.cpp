#include <gtest/gtest.h>

#include <iostream>

#include "../src/matrix.h"

TEST(MatrixAccess, AllowsUpdatingAnElement) {
    Matrix matrix(2, 2);

    std::cout << "Before setting element (1, 1):\n" << matrix << '\n';
    matrix.at(1, 1) = 42.5;
    std::cout << "After setting element (1, 1) to 42.5:\n" << matrix << '\n';

    EXPECT_DOUBLE_EQ(matrix.at(1, 1), 42.5);
}

TEST(MatrixAccess, ThrowsForOutOfRangeCoordinates) {
    Matrix matrix(2, 2);

    std::cout << "Reading coordinates outside this 2x2 matrix must throw std::out_of_range:\n"
              << matrix << '\n';
    EXPECT_THROW(matrix.at(2, 0), std::out_of_range);
    EXPECT_THROW(matrix.at(0, 2), std::out_of_range);
}
