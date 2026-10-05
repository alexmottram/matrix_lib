#include <gtest/gtest.h>

#include <iostream>
#include <limits>

#include "../src/matrix_lib.h"

TEST(MatrixConstruction, InitializesSizedMatrixWithZeros) {
    const Matrix matrix(3, 2);
    std::cout << "Constructing a 3x2 matrix initializes every element to zero:\n" << matrix << '\n';

    EXPECT_DOUBLE_EQ(matrix.at(0, 0), 0.0);
    EXPECT_DOUBLE_EQ(matrix.at(1, 0), 0.0);
    EXPECT_DOUBLE_EQ(matrix.at(2, 1), 0.0);
}

TEST(MatrixConstruction, RejectsDimensionsWhoseProductOverflows) {
    EXPECT_THROW(
        (Matrix(std::numeric_limits<size_t>::max(), 2)),
        std::length_error
    );
}

TEST(MatrixConstruction, ExposesRowAndColumnCounts) {
    const Matrix matrix(3, 2);

    EXPECT_EQ(matrix.row_count(), 2u);
    EXPECT_EQ(matrix.column_count(), 3u);
}

TEST(MatrixConstruction, BuildsFromInitializerLists) {
    const Matrix matrix{{1, 2, 3}, {4, 5, 6}};
    std::cout << "Constructing from nested initializer lists:\n" << matrix << '\n';

    EXPECT_DOUBLE_EQ(matrix.at(0, 0), 1.0);
    EXPECT_DOUBLE_EQ(matrix.at(2, 0), 3.0);
    EXPECT_DOUBLE_EQ(matrix.at(1, 1), 5.0);
}

TEST(MatrixConstruction, RejectsJaggedInitializerLists) {
    std::cout << "Constructing from jagged rows {{1, 2}, {3}} must throw std::invalid_argument.\n";
    EXPECT_THROW((Matrix{{1, 2}, {3}}), std::invalid_argument);
}
