#include <gtest/gtest.h>

#include <iostream>

#include "matrix/matrix_lib.h"

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

// ---- augment_columns: [this | other] ----

TEST(MatrixMatrixOperations, AugmentColumnsSquareWithColumnVector) {
    const Matrix a{{1, 2}, {3, 4}};
    const Matrix b{{5}, {6}};

    std::cout << "augment_columns of 2x2 A:\n" << a << "\nwith 2x1 b:\n" << b
              << "\nExpected a 2x3 matrix [A | b] = {{1,2,5},{3,4,6}}: same rows, columns 2+1,"
                 " every element checked by (column,row).\n";
    const Matrix result = a.augment_columns(b);
    std::cout << "Actual:\n" << result << '\n';

    ASSERT_EQ(result.row_count(), 2u);
    ASSERT_EQ(result.column_count(), 3u);
    EXPECT_DOUBLE_EQ(result.at(0, 0), 1);
    EXPECT_DOUBLE_EQ(result.at(1, 0), 2);
    EXPECT_DOUBLE_EQ(result.at(2, 0), 5);
    EXPECT_DOUBLE_EQ(result.at(0, 1), 3);
    EXPECT_DOUBLE_EQ(result.at(1, 1), 4);
    EXPECT_DOUBLE_EQ(result.at(2, 1), 6);
}

TEST(MatrixMatrixOperations, AugmentColumnsWithMultiColumnMatrix) {
    const Matrix a{{1, 2}, {3, 4}};
    const Matrix b{{5, 6, 7}, {8, 9, 10}};
    const Matrix expected{{1, 2, 5, 6, 7}, {3, 4, 8, 9, 10}};

    std::cout << "augment_columns of 2x2 A:\n" << a << "\nwith 2x3 B:\n" << b
              << "\nExpected a 2x5 matrix:\n" << expected << '\n';
    const Matrix result = a.augment_columns(b);
    std::cout << "Actual:\n" << result << '\n';

    ASSERT_EQ(result.row_count(), 2u);
    ASSERT_EQ(result.column_count(), 5u);
    EXPECT_TRUE(result == expected);
}

TEST(MatrixMatrixOperations, AugmentColumnsWithIdentity) {
    const Matrix a{{2, 1}, {5, 3}};
    const Matrix identity{{1, 0}, {0, 1}};
    const Matrix expected{{2, 1, 1, 0}, {5, 3, 0, 1}};

    std::cout << "Forming [A | I] for A:\n" << a << "\nand 2x2 identity:\n" << identity
              << "\nExpected the 2x4 matrix:\n" << expected << '\n';
    const Matrix result = a.augment_columns(identity);
    std::cout << "Actual:\n" << result << '\n';

    ASSERT_EQ(result.row_count(), 2u);
    ASSERT_EQ(result.column_count(), 4u);
    EXPECT_TRUE(result == expected);
}

TEST(MatrixMatrixOperations, AugmentColumnsTallNonSquareWithColumnVector) {
    const Matrix a{{1, 2}, {3, 4}, {5, 6}};
    const Matrix b{{7}, {8}, {9}};
    const Matrix expected{{1, 2, 7}, {3, 4, 8}, {5, 6, 9}};

    std::cout << "Non-square check (rows != columns): A is 3 rows x 2 columns:\n" << a
              << "\nb is 3x1:\n" << b
              << "\nExpected a 3x3 matrix; the result must have one row per row of A (3), not per"
                 " column of A (2):\n" << expected << '\n';
                     const Matrix result = a.augment_columns(b);
    std::cout << "Actual:\n" << result << '\n';

    ASSERT_EQ(result.row_count(), 3u);
    ASSERT_EQ(result.column_count(), 3u);
    EXPECT_TRUE(result == expected);
}

TEST(MatrixMatrixOperations, AugmentColumnsWideNonSquareWithTwoColumns) {
    const Matrix a{{1, 2, 3}, {4, 5, 6}};
    const Matrix b{{7, 8}, {9, 10}};
    const Matrix expected{{1, 2, 3, 7, 8}, {4, 5, 6, 9, 10}};

    std::cout << "Non-square check: A is 2 rows x 3 columns:\n" << a << "\nB is 2x2:\n" << b
              << "\nExpected a 2x5 matrix; iterating over A's 3 columns as if they were rows"
                 " would read past the 2 rows:\n" << expected << '\n';
                     const Matrix result = a.augment_columns(b);
    std::cout << "Actual:\n" << result << '\n';

    ASSERT_EQ(result.row_count(), 2u);
    ASSERT_EQ(result.column_count(), 5u);
    EXPECT_TRUE(result == expected);
}

TEST(MatrixMatrixOperations, AugmentColumnsSingleRow) {
    const Matrix a{{1, 2, 3}};
    const Matrix b{{4, 5}};
    const Matrix expected{{1, 2, 3, 4, 5}};

    std::cout << "Boundary: single-row 1x3 A:\n" << a << "\nwith 1x2 B:\n" << b
              << "\nExpected one row, 5 columns:\n" << expected << '\n';
                  const Matrix result = a.augment_columns(b);
    std::cout << "Actual:\n" << result << '\n';

    ASSERT_EQ(result.row_count(), 1u);
    ASSERT_EQ(result.column_count(), 5u);
    EXPECT_TRUE(result == expected);
}

TEST(MatrixMatrixOperations, AugmentColumnsSingleColumn) {
    const Matrix a{{1}, {2}, {3}};
    const Matrix b{{4}, {5}, {6}};
    const Matrix expected{{1, 4}, {2, 5}, {3, 6}};

    std::cout << "Boundary: single-column 3x1 A:\n" << a << "\nwith 3x1 B:\n" << b
              << "\nExpected a 3x2 matrix:\n" << expected << '\n';
                  const Matrix result = a.augment_columns(b);
    std::cout << "Actual:\n" << result << '\n';

    ASSERT_EQ(result.row_count(), 3u);
    ASSERT_EQ(result.column_count(), 2u);
    EXPECT_TRUE(result == expected);
}

TEST(MatrixMatrixOperations, AugmentColumnsSingleElement) {
    const Matrix a{{7}};
    const Matrix b{{9}};
    const Matrix expected{{7, 9}};

    std::cout << "Boundary: 1x1 A = {{7}} with 1x1 B = {{9}}; expected 1x2 {{7, 9}}.\n";
        const Matrix result = a.augment_columns(b);
    std::cout << "Actual:\n" << result << '\n';

    EXPECT_TRUE(result == expected);
}

TEST(MatrixMatrixOperations, AugmentColumnsMismatchedRowsThrowsLeftFewer) {
    const Matrix a{{1, 2}, {3, 4}};
    const Matrix b{{5}, {6}, {7}};

    std::cout << "Invalid input: A has 2 rows, b has 3 rows. Expected std::invalid_argument"
                 " because row counts differ.\n";
    EXPECT_THROW(static_cast<void>(a.augment_columns(b)), std::invalid_argument);
}

TEST(MatrixMatrixOperations, AugmentColumnsMismatchedRowsThrowsLeftMore) {
    const Matrix a{{1}, {2}, {3}};
    const Matrix b{{4, 5}, {6, 7}};

    std::cout << "Invalid input (reverse direction): A has 3 rows, B has 2 rows. Expected"
                 " std::invalid_argument because row counts differ.\n";
                     EXPECT_THROW(static_cast<void>(a.augment_columns(b)), std::invalid_argument);
}

TEST(MatrixMatrixOperations, AugmentColumnsDoesNotModifyInputs) {
    const Matrix a{{1, 2}, {3, 4}};
    const Matrix b{{5}, {6}};
    const Matrix a_before{{1, 2}, {3, 4}};
    const Matrix b_before{{5}, {6}};

    std::cout << "augment_columns is const and must leave both operands unchanged."
                 " A before:\n" << a_before << "\nb before:\n" << b_before << '\n';
    const Matrix result = a.augment_columns(b);
    std::cout << "After the call A:\n" << a << "\nb:\n" << b << "\nresult:\n" << result << '\n';

    EXPECT_TRUE(a == a_before);
    EXPECT_TRUE(b == b_before);
    EXPECT_EQ(a.row_count(), 2u);
    EXPECT_EQ(a.column_count(), 2u);
    EXPECT_EQ(b.row_count(), 2u);
    EXPECT_EQ(b.column_count(), 1u);
}
