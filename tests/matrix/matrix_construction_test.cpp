#include <gtest/gtest.h>

#include <iostream>
#include <limits>
#include <stdexcept>
#include <vector>

#include "matrix/matrix_lib.h"

TEST(MatrixConstruction, InitializesSizedMatrixWithZeros) {
    const Matrix matrix(3, 2);
    std::cout << "Constructing a 3x2 matrix initializes every element to zero:\n" << matrix << '\n';

    EXPECT_DOUBLE_EQ(matrix.at(0, 0), 0.0);
    EXPECT_DOUBLE_EQ(matrix.at(1, 0), 0.0);
    EXPECT_DOUBLE_EQ(matrix.at(2, 1), 0.0);
}

TEST(MatrixConstruction, RejectsDimensionsWhoseProductOverflows) {
    std::cout << "Constructing a matrix with SIZE_MAX columns and 2 rows must reject the overflowing element count with std::length_error.\n";
    EXPECT_THROW(
        (Matrix(std::numeric_limits<size_t>::max(), 2)),
        std::length_error
    );
}

TEST(MatrixConstruction, ExposesRowAndColumnCounts) {
    const Matrix matrix(3, 2);

    std::cout << "A Matrix constructed with 3 columns and 2 rows reports row_count() == 2 and column_count() == 3.\n";
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

TEST(MatrixVectorConstruction, Builds2x3FromNestedVectors) {
    const std::vector<std::vector<double>> values{{1, 2, 3}, {4, 5, 6}};
    const Matrix matrix(values);
    std::cout << "Constructing from a vector of 2 rows with 3 values each ({{1,2,3},{4,5,6}}) must give "
                 "row_count()==2, column_count()==3, and at(x, y) == values[y][x]:\n" << matrix << '\n';

    EXPECT_EQ(matrix.row_count(), 2u);
    EXPECT_EQ(matrix.column_count(), 3u);
    for (size_t y = 0; y < 2; ++y) {
        for (size_t x = 0; x < 3; ++x) {
            EXPECT_DOUBLE_EQ(matrix.at(x, y), values[y][x]) << "at x=" << x << " y=" << y;
        }
    }
}

TEST(MatrixVectorConstruction, Builds3x2FromNestedVectors) {
    const std::vector<std::vector<double>> values{{1, 2}, {3, 4}, {5, 6}};
    const Matrix matrix(values);
    std::cout << "Constructing from a vector of 3 rows with 2 values each ({{1,2},{3,4},{5,6}}) must give "
                 "row_count()==3, column_count()==2 (non-square, so rows/columns are not confused):\n" << matrix << '\n';

    EXPECT_EQ(matrix.row_count(), 3u);
    EXPECT_EQ(matrix.column_count(), 2u);
    for (size_t y = 0; y < 3; ++y) {
        for (size_t x = 0; x < 2; ++x) {
            EXPECT_DOUBLE_EQ(matrix.at(x, y), values[y][x]) << "at x=" << x << " y=" << y;
        }
    }
    EXPECT_THROW((void)matrix.at(2, 0), std::out_of_range);
    EXPECT_THROW((void)matrix.at(0, 3), std::out_of_range);
}

TEST(MatrixVectorConstruction, BuildsSingleRow) {
    const std::vector<std::vector<double>> values{{7, 8, 9, 10}};
    const Matrix matrix(values);
    std::cout << "Boundary: a single row {{7,8,9,10}} gives a 1-row, 4-column matrix:\n" << matrix << '\n';

    EXPECT_EQ(matrix.row_count(), 1u);
    EXPECT_EQ(matrix.column_count(), 4u);
    EXPECT_DOUBLE_EQ(matrix.at(0, 0), 7.0);
    EXPECT_DOUBLE_EQ(matrix.at(3, 0), 10.0);
}

TEST(MatrixVectorConstruction, BuildsSingleColumn) {
    const std::vector<std::vector<double>> values{{7}, {8}, {9}, {10}};
    const Matrix matrix(values);
    std::cout << "Boundary: four rows of one value {{7},{8},{9},{10}} gives a 4-row, 1-column matrix:\n" << matrix << '\n';

    EXPECT_EQ(matrix.row_count(), 4u);
    EXPECT_EQ(matrix.column_count(), 1u);
    EXPECT_DOUBLE_EQ(matrix.at(0, 0), 7.0);
    EXPECT_DOUBLE_EQ(matrix.at(0, 3), 10.0);
}

TEST(MatrixVectorConstruction, EmptyOuterVectorGivesEmptyMatrix) {
    const std::vector<std::vector<double>> values;
    const Matrix matrix(values);
    std::cout << "Boundary: an empty outer vector must not throw and gives a 0x0 matrix: "
                 "no elements, any at() throws std::out_of_range, begin()==end(), equal to Matrix(0, 0).\n";

    EXPECT_EQ(matrix.row_count(), 0u);
    EXPECT_EQ(matrix.column_count(), 0u);
    EXPECT_THROW((void)matrix.at(0, 0), std::out_of_range);
    EXPECT_TRUE(matrix.begin() == matrix.end());
    EXPECT_TRUE(matrix == Matrix(0, 0));
}

TEST(MatrixVectorConstruction, VectorOfEmptyRowsGivesZeroColumnMatrix) {
    const std::vector<std::vector<double>> values(3);
    const Matrix matrix(values);
    std::cout << "Boundary: 3 empty rows ({{},{},{}}) are consistent (all length 0), so construction succeeds "
                 "with row_count()==3, column_count()==0 and no elements.\n";

    EXPECT_EQ(matrix.row_count(), 3u);
    EXPECT_EQ(matrix.column_count(), 0u);
    EXPECT_THROW((void)matrix.at(0, 0), std::out_of_range);
    EXPECT_TRUE(matrix.begin() == matrix.end());
    EXPECT_TRUE(matrix == Matrix(0, 3));
}

TEST(MatrixVectorConstruction, RejectsRaggedFirstRow) {
    const std::vector<std::vector<double>> values{{1}, {2, 3}, {4, 5}};
    std::cout << "Ragged first row {{1},{2,3},{4,5}} (first row shorter) must throw std::invalid_argument.\n";
    EXPECT_THROW((Matrix(values)), std::invalid_argument);
}

TEST(MatrixVectorConstruction, RejectsRaggedMiddleRow) {
    const std::vector<std::vector<double>> values{{1, 2}, {3}, {4, 5}};
    std::cout << "Ragged middle row {{1,2},{3},{4,5}} must throw std::invalid_argument.\n";
    EXPECT_THROW((Matrix(values)), std::invalid_argument);
}

TEST(MatrixVectorConstruction, RejectsRaggedLastRow) {
    const std::vector<std::vector<double>> values{{1, 2}, {3, 4}, {5, 6, 7}};
    std::cout << "Ragged last row {{1,2},{3,4},{5,6,7}} must throw std::invalid_argument.\n";
    EXPECT_THROW((Matrix(values)), std::invalid_argument);
}

TEST(MatrixVectorConstruction, RejectsEmptyRowAmongNonEmptyRows) {
    const std::vector<std::vector<double>> values{{1, 2}, {}};
    std::cout << "Boundary: an empty row after a non-empty row {{1,2},{}} is ragged and must throw std::invalid_argument.\n";
    EXPECT_THROW((Matrix(values)), std::invalid_argument);
}

TEST(MatrixVectorConstruction, DoesNotModifyInputVector) {
    const std::vector<std::vector<double>> values{{1, 2, 3}, {4, 5, 6}};
    std::vector<std::vector<double>> input = values;
    std::cout << "The constructor takes a const reference, so the input {{1,2,3},{4,5,6}} must be unchanged "
                 "afterwards, and changing the matrix must not alter the input (the matrix owns a copy).\n";

    Matrix matrix(input);
    matrix.at(0, 0) = 100.0;
    std::cout << "Matrix element (0,0) changed from 1 to 100; input[0][0] should still be 1.\n";

    EXPECT_EQ(input, values);
    EXPECT_DOUBLE_EQ(input[0][0], 1.0);
    EXPECT_DOUBLE_EQ(matrix.at(0, 0), 100.0);
}

TEST(MatrixVectorConstruction, EqualsInitializerListConstructedMatrix) {
    const std::vector<std::vector<double>> values{{1, 2, 3}, {4, 5, 6}};
    const Matrix from_vector(values);
    const Matrix from_list{{1, 2, 3}, {4, 5, 6}};
    std::cout << "A matrix built from vector {{1,2,3},{4,5,6}} must compare equal to the one built from the "
                 "same initializer list, and unequal to a transposed-shape matrix with the same values.\n";

    EXPECT_TRUE(from_vector == from_list);
    const Matrix reshaped{{1, 2}, {3, 4}, {5, 6}};
    EXPECT_FALSE(from_vector == reshaped);
}

TEST(MatrixConstruction, RejectsJaggedInitializerLists) {
    std::cout << "Constructing from jagged rows {{1, 2}, {3}} must throw std::invalid_argument.\n";
    EXPECT_THROW((Matrix{{1, 2}, {3}}), std::invalid_argument);
}
