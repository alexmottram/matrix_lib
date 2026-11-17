#include <gtest/gtest.h>

#include <cmath>
#include <iostream>
#include <iterator>
#include <ranges>

#include "matrix/matrix_lib.h"
#include "utils/std_extensions.h"

TEST(MatrixIterator, RowIteratorReturnsAllRowViews) {
    Matrix matrix{{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
    const std::vector<double> expected_row_vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    std::cout << "Iterating over all row views should flatten the matrix in row-major order:\n" << matrix << '\n';
    std::vector<double> flattened_row_vec {};
    for (auto [row_index, row_view] : matrix.rows()) {
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
    std::cout << "Doubling even values in row 1 (zero-based) should leave the other rows unchanged.\n"
              << "Before:\n" << matrix << '\n';
    std::vector<double> flattened_row_vec {};
    for (auto [row_index, row_view] : matrix.rows()) {
        if (row_index == 1) {
            for (const auto val: row_view) {
                if (std::fmod(val.value, 2.0) == 0.0) {
                    std::cout << "Doubling even value " << val.value << " at (column " << val.x
                              << ", row " << val.y << ") to " << val.value * 2 << ".\n";
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
    std::cout << "Reading all rows of a const matrix in row-major order without modifying its values:\n" << matrix << '\n';
    std::vector<double> flattened {};
    size_t rows = 0;
    for (auto [row_index, row_view] : matrix.rows()) {
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
    std::cout << "Reading each column view top-to-bottom from this matrix:\n" << matrix << '\n';
    std::vector<double> flattened {};
    size_t columns = 0;
    for (auto [column_index, column_view] : matrix.columns()) {
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
    std::cout << "Doubling only even values in column 1 (zero-based):\nBefore:\n" << matrix << '\n';
    for (auto [column_index, column_view] : matrix.columns()) {
        if (column_index == 1) {
            for (const auto val : column_view) {
                if (std::fmod(val.value, 2.0) == 0.0) {
                    std::cout << "Doubling even value " << val.value << " at (column " << val.x
                              << ", row " << val.y << ") to " << val.value * 2 << ".\n";
                    val.value *= 2;
                }
            }
        }
    }
    std::cout << "After updating column 1:\n" << matrix << "\nExpected:\n" << expected << '\n';
    EXPECT_EQ(matrix, expected);
}

TEST(MatrixIterator, ConstColumnIteratorReadsAllColumnsWithoutModification) {
    const Matrix matrix{{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
    std::cout << "Reading every column of a const matrix top-to-bottom without modifying its values:\n" << matrix << '\n';
    std::vector<double> flattened {};
    size_t columns = 0;
    for (auto [column_index, column_view] : matrix.columns()) {
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

TEST(MatrixIterator, SliceIteratorsAreRandomAccess) {
    std::cout << "Verifying row, column, and slice iterators satisfy the C++ random-access iterator and range concepts.\n";
    static_assert(std::random_access_iterator<Matrix::RowIterator>);
    static_assert(std::random_access_iterator<Matrix::ConstRowIterator>);
    static_assert(std::random_access_iterator<Matrix::ColumnIterator>);
    static_assert(std::random_access_iterator<Matrix::ConstColumnIterator>);
    static_assert(std::random_access_iterator<Matrix::RowViewIterator>);
    static_assert(std::random_access_iterator<Matrix::ConstRowViewIterator>);
    static_assert(std::random_access_iterator<Matrix::ColumnViewIterator>);
    static_assert(std::random_access_iterator<Matrix::ConstColumnViewIterator>);
    static_assert(std::ranges::random_access_range<Matrix::RowRange>);
    static_assert(std::ranges::random_access_range<Matrix::ConstColumnRange>);
    static_assert(std::ranges::sized_range<Matrix::RowRange>);
    SUCCEED();
}

TEST(MatrixIterator, SliceIteratorsSupportJumpsAndDistances) {
    Matrix matrix{{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
    std::cout << "Checking iterator offsets, indexed jumps, ordering, and distances across matrix rows, columns, and slices:\n" << matrix << '\n';
    auto rows = matrix.rows();
    EXPECT_EQ(rows.end() - rows.begin(), 3);
    EXPECT_EQ(rows.begin()[2].row_index, 2u);
    EXPECT_EQ((*(rows.end() - 1)).row_index, 2u);
    EXPECT_LT(rows.begin(), rows.end());
    EXPECT_EQ(std::ranges::size(matrix.columns()), 4u);
    EXPECT_EQ(matrix.columns().begin()[3].column_view.at(2), 12);

    const auto row = matrix.row_at(1);
    EXPECT_EQ(row.end() - row.begin(), 4);
    EXPECT_EQ(row.begin()[2].value, 7);
    EXPECT_EQ((*(row.end() - 1)).value, 8);

    const auto column = matrix.column_at(2);
    EXPECT_EQ(column.begin()[2].value, 11);
    auto it = column.end();
    --it;
    EXPECT_EQ((*it).y, 2u);
}

TEST(MatrixIterator, ReverseViewOverRowsVisitsRowsBackwards) {
    const Matrix matrix{{1, 2}, {3, 4}, {5, 6}};
    std::cout << "Reversing the row range should visit row indices 2, 1, 0 for this matrix:\n" << matrix << '\n';
    std::vector<size_t> order;
    for (auto [row_index, row_view] : std::views::reverse(matrix.rows())) {
        order.push_back(row_index);
    }
    EXPECT_EQ(order, (std::vector<size_t>{2, 1, 0}));
}
