#include <gtest/gtest.h>

#include <iostream>

#include "../src/matrix.h"

TEST(MatrixMatrixOperations, TransposeRowVector) {
    const Matrix original_matrix{{1, 2, 3, 4}};
    const Matrix expected{{1}, {2}, {3}, {4}};

    const Matrix transposed_matrix = original_matrix.transpose();
    std::cout << "Transposing a row vector:\n" << original_matrix
              << "\nbecomes:\n" << transposed_matrix << '\n';
    EXPECT_TRUE(transposed_matrix == expected);

    const Matrix double_transposed_matrix = transposed_matrix.transpose();
    std::cout << "Transposing it again restores:\n" << double_transposed_matrix << '\n';
    EXPECT_TRUE(double_transposed_matrix == original_matrix);
}

TEST(MatrixMatrixOperations, TransposeColumnVector) {
    const Matrix original_matrix{{1}, {2}, {3}, {4}};
    const Matrix expected{{1, 2, 3, 4}};

    const Matrix transposed_matrix = original_matrix.transpose();
    std::cout << "Transposing a column vector:\n" << original_matrix
              << "\nbecomes:\n" << transposed_matrix << '\n';
    EXPECT_TRUE(transposed_matrix == expected);

    const Matrix double_transposed_matrix = transposed_matrix.transpose();
    std::cout << "Transposing it again restores:\n" << double_transposed_matrix << '\n';
    EXPECT_TRUE(double_transposed_matrix == original_matrix);
}

TEST(MatrixMatrixOperations, TransposeMatrix) {
    const Matrix original_matrix{{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
    const Matrix expected{{1, 5, 9}, {2, 6, 10}, {3, 7, 11}, {4, 8, 12}};

    const Matrix transposed_matrix = original_matrix.transpose();
    std::cout << "Transposing a 3x4 matrix:\n" << original_matrix
              << "\nbecomes:\n" << transposed_matrix << '\n';
    EXPECT_TRUE(transposed_matrix == expected);

    const Matrix double_transposed_matrix = transposed_matrix.transpose();
    std::cout << "Transposing it again restores:\n" << double_transposed_matrix << '\n';
    EXPECT_TRUE(double_transposed_matrix == original_matrix);
}
