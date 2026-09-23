#include <gtest/gtest.h>

#include <iostream>

#include "../src/matrix.h"

TEST(MatrixBasicArithmetic, BasicMatrixAddition) {
    const Matrix matrix_a{{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
    const Matrix matrix_b{{10, 10, 10, 10}, {20, 20, 20, 20}, {30, 30, 30, 30}};
    const Matrix expected{{11, 12, 13, 14}, {25, 26, 27, 28}, {39, 40, 41, 42}};

    const auto matrix_sum = matrix_a + matrix_b;
    const auto matrix_sum_reverse = matrix_b + matrix_a;

    std::cout << "Adding matrices:\n" << matrix_a << "\n+\n" << matrix_b
              << "\n=\n" << matrix_sum << '\n';
    std::cout << "Reversing the operands produces:\n" << matrix_sum_reverse << '\n';
    EXPECT_TRUE(matrix_sum == expected);
    EXPECT_TRUE(matrix_sum_reverse == expected);
}

TEST(MatrixBasicArithmetic, BasicMatrixSubtraction) {
    const Matrix matrix_a{{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
    const Matrix matrix_b{{10, 10, 10, 10}, {20, 20, 20, 20}, {30, 30, 30, 30}};
    const Matrix expected_a_minus_b{{-9, -8, -7, -6}, {-15, -14, -13, -12}, {-21, -20, -19, -18}};
    const Matrix expected_b_minus_a{{9, 8, 7, 6}, {15, 14, 13, 12}, {21, 20, 19, 18}};

    const auto matrix_a_minus_b = matrix_a - matrix_b;
    const auto matrix_b_minus_a = matrix_b - matrix_a;

    std::cout << "Subtracting matrices:\n" << matrix_a << "\n-\n" << matrix_b
              << "\n=\n" << matrix_a_minus_b << '\n';
    std::cout << "Reversing the operands produces:\n" << matrix_b_minus_a << '\n';
    EXPECT_TRUE(matrix_a_minus_b == expected_a_minus_b);
    EXPECT_TRUE(matrix_b_minus_a == expected_b_minus_a);
}

TEST(MatrixBasicArithmetic, BasicMatrixOuterProductWithColumnAndRowVectors) {
    const Matrix column_vector{{1}, {2}, {3}};
    const Matrix row_vector{{4, 5, 6}};
    const Matrix expected_outer_product{{4, 5, 6}, {8, 10, 12}, {12, 15, 18}};

    const auto matrix_outer_product = column_vector * row_vector;

    std::cout << "Computing an outer product:\n" << column_vector << "\n*\n" << row_vector
              << "\n=\n" << matrix_outer_product << '\n';
    EXPECT_TRUE(matrix_outer_product == expected_outer_product);
}

TEST(MatrixBasicArithmetic, BasicMatrixOuterProductWithNegativeValues) {
    const Matrix column_vector{{2}, {-1}, {4}};
    const Matrix row_vector{{3, 0, -5}};
    const Matrix expected_outer_product{{6, 0, -10}, {-3, 0, 5}, {12, 0, -20}};

    const auto matrix_outer_product = column_vector * row_vector;

    std::cout << "Computing an outer product with negative values:\n"
              << column_vector << "\n*\n" << row_vector << "\n=\n" << matrix_outer_product << '\n';
    EXPECT_TRUE(matrix_outer_product == expected_outer_product);
}

TEST(MatrixBasicArithmetic, BasicMatrixMultiplicationTwoMatrices) {
    const Matrix matrix_a{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10, 11, 12}, {13, 14, 15}};
    const Matrix matrix_b{{1, 0, 2, 0, 3, 4}, {5, 6, 7, 8, 9, 10}, {11, 12, 13, 14, 15, 16}};
    const Matrix expected_product{
        {44, 48, 55, 58, 66, 72},
        {95, 102, 121, 124, 147, 162},
        {146, 156, 187, 190, 228, 252},
        {197, 210, 253, 256, 309, 342},
        {248, 264, 319, 322, 390, 432}
    };

    const auto matrix_product = matrix_a * matrix_b;

    std::cout << "Multiplying a 5x3 matrix by a 3x6 matrix:\n" << matrix_a << "\n*\n"
              << matrix_b << "\n=\n" << matrix_product << '\n';
    EXPECT_TRUE(matrix_product == expected_product);
}

TEST(MatrixBasicArithmetic, BasicMatrixMultiplicationVectorOuterProduct) {
    const Matrix matrix_a{{1}, {2}, {3}, {4}};
    const Matrix matrix_b{{5, 6, 7, 8}};
    const Matrix expected_product{{5, 6, 7, 8}, {10, 12, 14, 16}, {15, 18, 21, 24}, {20, 24, 28, 32}};

    const auto matrix_product = matrix_a * matrix_b;

    std::cout << "Multiplying a column vector by a row vector:\n" << matrix_a << "\n*\n"
              << matrix_b << "\n=\n" << matrix_product << '\n';
    EXPECT_TRUE(matrix_product == expected_product);
}

TEST(MatrixBasicArithmetic, BasicMatrixMultiplicationVectorInnerProduct) {
    const Matrix matrix_a{{1, 2, 3, 4}};
    const Matrix matrix_b{{5}, {6}, {7}, {8}};
    const Matrix expected_product{{70}};

    const auto matrix_product = matrix_a * matrix_b;

    std::cout << "Multiplying a row vector by a column vector (inner product):\n"
              << matrix_a << "\n*\n" << matrix_b << "\n=\n" << matrix_product << '\n';
    EXPECT_TRUE(matrix_product == expected_product);
}

TEST(MatrixBasicArithmetic, BasicMatrixScalarProduct) {
    const Matrix matrix{{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
    const Matrix expected_scalar_product{{10, 20, 30, 40}, {50, 60, 70, 80}, {90, 100, 110, 120}};

    const auto matrix_scalar_product = matrix * 10;
    const auto matrix_scalar_product_reverse = 10 * matrix;

    std::cout << "Multiplying a matrix by scalar 10:\n" << matrix << "\n*\n10\n=\n"
              << matrix_scalar_product << '\n';
    std::cout << "Using scalar-first multiplication produces:\n"
              << matrix_scalar_product_reverse << '\n';
    EXPECT_TRUE(matrix_scalar_product == expected_scalar_product);
    EXPECT_TRUE(matrix_scalar_product_reverse == expected_scalar_product);
}
