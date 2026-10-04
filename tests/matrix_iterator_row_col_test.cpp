#include <gtest/gtest.h>

#include <cmath>
#include <iostream>

#include "../src/matrix.h"

TEST(MatrixIterator, RowIteratorReturnsAllRowViews) {
    Matrix matrix{{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
    const std::vector<double> expected_row_vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    std::cout << "Starting row view tests..." << std::endl;
    std::vector<double> flattened_row_vec {};
    for (auto [row_index, row_view] : matrix.row_iterator()) {
        std::cout << "Row index: " << row_index << ", Row view: " << row_view << std::endl;
        for (auto val: row_view) {
            flattened_row_vec.push_back(val.value);
        }
    }
    std::cout << "Flattened row vector: " << flattened_row_vec << std::endl;
    std::cout << "Expected row vector: " << expected_row_vec << std::endl;

    EXPECT_EQ(flattened_row_vec.size(), expected_row_vec.size());
    // TODO -> add the value check after
}


TEST(MatrixIterator, RowIteratorUpdatesEvensInRowIdx1) {
    Matrix matrix{{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
    const Matrix expected_output_matrix{{1, 2, 3, 4}, {5, 12, 7, 16}, {9, 10, 11, 12}};
    const std::vector<double> expected_row_vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    std::cout << "Starting row view tests..." << std::endl;
    std::vector<double> flattened_row_vec {};
    for (auto [row_index, row_view] : matrix.row_iterator()) {
        if (row_index == 1) {
            for (const auto val: row_view) {
                if (std::fmod(val.value, 2.0) == 0.0) {
                    val.value *= 2;
                }
            }
        }
    }
    std::cout << "Matrix modified by row vector: \n" << matrix << std::endl;
    std::cout << "Expected matrix: \n" << expected_output_matrix << std::endl;

    EXPECT_EQ(matrix, expected_output_matrix);
}

TEST(MatrixIterator, ConstRowIteratorReadsAllRowsWithoutModification) {
    const Matrix matrix{{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
    std::vector<double> flattened {};
    size_t rows = 0;
    for (auto [row_index, row_view] : matrix.row_iterator()) {
        EXPECT_EQ(row_index, rows++);
        for (auto val : row_view) {
            static_assert(std::is_const_v<std::remove_reference_t<decltype(val.value)>>);
            flattened.push_back(val.value);
        }
    }
    const std::vector<double> expected = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    EXPECT_EQ(rows, 3);
    EXPECT_EQ(flattened, expected);
}

TEST(MatrixIterator, ColumnIteratorReturnsAllColumnViews) {
    Matrix matrix{{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
    std::vector<double> flattened {};
    size_t columns = 0;
    for (auto [column_index, column_view] : matrix.column_iterator()) {
        EXPECT_EQ(column_index, columns++);
        for (auto val : column_view) {
            flattened.push_back(val.value);
        }
    }
    const std::vector<double> expected = {1, 5, 9, 2, 6, 10, 3, 7, 11, 4, 8, 12};
    EXPECT_EQ(columns, 4);
    EXPECT_EQ(flattened, expected);
}

TEST(MatrixIterator, ColumnIteratorUpdatesEvensInColumnIdx1) {
    Matrix matrix{{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
    const Matrix expected{{1, 4, 3, 4}, {5, 12, 7, 8}, {9, 20, 11, 12}};
    for (auto [column_index, column_view] : matrix.column_iterator()) {
        if (column_index == 1) {
            for (const auto val : column_view) {
                if (std::fmod(val.value, 2.0) == 0.0) {
                    val.value *= 2;
                }
            }
        }
    }
    EXPECT_EQ(matrix, expected);
}

TEST(MatrixIterator, ConstColumnIteratorReadsAllColumnsWithoutModification) {
    const Matrix matrix{{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
    std::vector<double> flattened {};
    size_t columns = 0;
    for (auto [column_index, column_view] : matrix.column_iterator()) {
        EXPECT_EQ(column_index, columns++);
        for (auto val : column_view) {
            static_assert(std::is_const_v<std::remove_reference_t<decltype(val.value)>>);
            flattened.push_back(val.value);
        }
    }
    const std::vector<double> expected = {1, 5, 9, 2, 6, 10, 3, 7, 11, 4, 8, 12};
    EXPECT_EQ(columns, 4);
    EXPECT_EQ(flattened, expected);
}
