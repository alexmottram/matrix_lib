#include <gtest/gtest.h>

#include <iostream>

#include "../src/matrix_lib.h"

TEST(MatrixComparison, TwoByTwoMatricesWithSameValuesAreEqual) {
    const Matrix matrix_a({{1, 2}, {3, 4}});
    const Matrix matrix_b({{1, 2}, {3, 4}});

    std::cout << "Comparing equal matrices:\n" << matrix_a << "\n==\n" << matrix_b << '\n';
    EXPECT_TRUE(matrix_a == matrix_b);
}

TEST(MatrixComparison, TwoByTwoMatricesWithDifferentValuesAreNotEqual) {
    const Matrix matrix_a({{1, 2}, {3, 4}});
    const Matrix matrix_b({{1, 2}, {3, 5}});

    std::cout << "Comparing matrices with different values:\n" << matrix_a << "\n!=\n" << matrix_b << '\n';
    EXPECT_FALSE(matrix_a == matrix_b);
}

TEST(MatrixComparison, MatricesWithDifferentRowsAreNotEqual) {
    const Matrix matrix_a({{1, 2, 3}, {4, 5, 6}});
    const Matrix matrix_b({{1, 2}, {3, 4}});

    std::cout << "Comparing matrices with different column counts:\n"
              << matrix_a << "\n!=\n" << matrix_b << '\n';
    EXPECT_FALSE(matrix_a == matrix_b);
}

TEST(MatrixComparison, MatricesWithDifferentColumnsAreNotEqual) {
    const Matrix matrix_a({{1, 2}, {3, 4}, {5, 6}});
    const Matrix matrix_b({{1, 2}, {3, 4}});

    std::cout << "Comparing matrices with different row counts:\n"
              << matrix_a << "\n!=\n" << matrix_b << '\n';
    EXPECT_FALSE(matrix_a == matrix_b);
}