#include <gtest/gtest.h>

#include <iostream>

#include "matrix/matrix_lib.h"

TEST(MatrixProperties, OneByOneIsSquare) {
    const Matrix matrix{{5}};
    std::cout << "A 1x1 matrix (smallest boundary case) has size_x == size_y, so is_square() should be true:\n"
              << matrix << '\n';
    EXPECT_TRUE(matrix.is_square());
}

TEST(MatrixProperties, ThreeByThreeIsSquare) {
    const Matrix matrix{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    std::cout << "A 3x3 matrix has equal row and column counts, so is_square() should be true:\n"
              << matrix << '\n';
    EXPECT_TRUE(matrix.is_square());
}

TEST(MatrixProperties, TwoRowsThreeColumnsIsNotSquare) {
    const Matrix matrix{{1, 2, 3}, {4, 5, 6}};
    std::cout << "A matrix with 2 rows and 3 columns has differing dimensions, so is_square() should be false:\n"
              << matrix << '\n';
    EXPECT_FALSE(matrix.is_square());
}

TEST(MatrixProperties, ThreeRowsTwoColumnsIsNotSquare) {
    const Matrix matrix{{1, 2}, {3, 4}, {5, 6}};
    std::cout << "A matrix with 3 rows and 2 columns has differing dimensions, so is_square() should be false:\n"
              << matrix << '\n';
    EXPECT_FALSE(matrix.is_square());
}

TEST(MatrixProperties, RowVectorIsNotSquare) {
    const Matrix matrix{{1, 2, 3}};
    std::cout << "A 1x3 row vector has one row and three columns, so is_square() should be false:\n"
              << matrix << '\n';
    EXPECT_FALSE(matrix.is_square());
}

TEST(MatrixProperties, ColumnVectorIsNotSquare) {
    const Matrix matrix{{1}, {2}, {3}};
    std::cout << "A 3x1 column vector has three rows and one column, so is_square() should be false:\n"
              << matrix << '\n';
    EXPECT_FALSE(matrix.is_square());
}

TEST(MatrixProperties, TransposePreservesSquareness) {
    const Matrix square{{1, 2}, {3, 4}};
    const Matrix non_square{{1, 2, 3}, {4, 5, 6}};
    std::cout << "Transposing swaps dimensions, so a 2x2 matrix stays square and a 2x3 matrix stays non-square.\n"
              << "2x2 transposed:\n" << square.transpose()
              << "\n2x3 transposed:\n" << non_square.transpose() << '\n';
    EXPECT_TRUE(square.transpose().is_square());
    EXPECT_FALSE(non_square.transpose().is_square());
}

TEST(MatrixProperties, SizeTConstructorSquare) {
    const Matrix matrix(4, 4);
    std::cout << "Matrix(4, 4) built with the size_t constructor has equal dimensions, so is_square() should be true:\n"
              << matrix << '\n';
    EXPECT_TRUE(matrix.is_square());
}

TEST(MatrixProperties, SizeTConstructorNonSquare) {
    const Matrix matrix(2, 5);
    std::cout << "Matrix(2, 5) built with the size_t constructor has differing dimensions, so is_square() should be false:\n"
              << matrix << '\n';
    EXPECT_FALSE(matrix.is_square());
}
