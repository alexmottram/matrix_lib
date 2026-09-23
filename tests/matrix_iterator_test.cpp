#include <gtest/gtest.h>

#include <iostream>

#include "../src/matrix.h"

TEST(MatrixIterator, UpdatesMultiplesOfThreeThroughCoordinatesAndReference) {
    Matrix matrix{{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
    const Matrix expected{{1, 2, 6, 4}, {5, 12, 7, 8}, {18, 10, 11, 24}};

    std::cout << "Iterating by coordinates and reference; doubling values divisible by three.\n"
              << "Before:\n" << matrix << '\n';
    for (auto [x, y, value] : matrix) {
        EXPECT_DOUBLE_EQ(value, matrix.at(x, y));

        if (static_cast<int>(value) % 3 == 0) {
            value *= 2;
        }
    }

    std::cout << "After:\n" << matrix << '\n';
    EXPECT_TRUE(matrix == expected);
}
