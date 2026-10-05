#include <gtest/gtest.h>

#include <iostream>

#include "../src/matrix_lib.h"

template <typename DestinationMatrix, typename SourceMatrix>
concept CanReplaceMatrixRow = requires(DestinationMatrix& destination, SourceMatrix& source) {
    destination.row_at(0).replace(source.row_at(0));
};

template <typename DestinationMatrix, typename SourceMatrix>
concept CanReplaceMatrixColumn = requires(DestinationMatrix& destination, SourceMatrix& source) {
    destination.column_at(0).replace(source.column_at(0));
};

// static_assert is a valid statement inside a TEST body, so these compile-time
// checks get a named entry in the gtest output instead of being invisible
// file-scope code. A violation still fails the build rather than the test run.
TEST(MatrixAccessRowColumn, RowColumnViewsExposeConstCorrectElementReferences) {
    // A const Matrix only ever exposes read-only row/column views (const
    // double&), so its elements cannot be mutated.
    static_assert(std::is_same_v<decltype(std::declval<const Matrix&>().row_at(0).at(0)), const double&>);
    static_assert(std::is_same_v<decltype(std::declval<const Matrix&>().column_at(0).at(0)), const double&>);
    static_assert(std::is_same_v<decltype(std::declval<Matrix&>().row_at(0).at(0)), double&>);
    static_assert(std::is_same_v<decltype(std::declval<Matrix&>().column_at(0).at(0)), double&>);
}

TEST(MatrixAccessRowColumn, ReplaceIsOnlyAvailableOnMutableMatrixRowViews) {
    static_assert(CanReplaceMatrixRow<Matrix, Matrix>);
    static_assert(CanReplaceMatrixRow<Matrix, const Matrix>);
    static_assert(!CanReplaceMatrixRow<const Matrix, Matrix>);
    static_assert(!CanReplaceMatrixRow<const Matrix, const Matrix>);
}

TEST(MatrixAccessRowColumn, ReplaceIsOnlyAvailableOnMutableMatrixColumnViews) {
    static_assert(CanReplaceMatrixColumn<Matrix, Matrix>);
    static_assert(CanReplaceMatrixColumn<Matrix, const Matrix>);
    static_assert(!CanReplaceMatrixColumn<const Matrix, Matrix>);
    static_assert(!CanReplaceMatrixColumn<const Matrix, const Matrix>);
}

TEST(MatrixAccessRowColumn, RowAtReadsElements) {
    const Matrix matrix{{1, 2, 3}, {4, 5, 6}};
    const auto row = matrix.row_at(1);

    std::cout << "Reading row 1 of:\n" << matrix << '\n';
    std::cout << "Row 1:\n" << row << '\n';
    EXPECT_EQ(row.size(), 3u);
    EXPECT_DOUBLE_EQ(row.at(0), 4.0);
    EXPECT_DOUBLE_EQ(row.at(1), 5.0);
    EXPECT_DOUBLE_EQ(row.at(2), 6.0);
}

TEST(MatrixAccessRowColumn, ColumnAtReadsElements) {
    const Matrix matrix{{1, 2, 3}, {4, 5, 6}};
    const auto column = matrix.column_at(2);

    std::cout << "Reading column 2 of:\n" << matrix << '\n';

    EXPECT_EQ(column.size(), 2u);
    EXPECT_DOUBLE_EQ(column.at(0), 3.0);
    EXPECT_DOUBLE_EQ(column.at(1), 6.0);
}

TEST(MatrixAccessRowColumn, RowAtAllowsMutationOfNonConstMatrix) {
    Matrix matrix{{1, 2, 3}, {4, 5, 6}};

    std::cout << "Before setting element (1, 0) via row_at(0):\n" << matrix << '\n';
    const auto row = matrix.row_at(0);
    row.at(1) = 42.0;
    std::cout << "After setting element (1, 0) to 42.0:\n" << matrix << '\n';

    EXPECT_DOUBLE_EQ(matrix.at(1, 0), 42.0);
}

TEST(MatrixAccessRowColumn, ColumnAtAllowsMutationOfNonConstMatrix) {
    Matrix matrix{{1, 2, 3}, {4, 5, 6}};

    std::cout << "Before setting element (0, 1) via column_at(0):\n" << matrix << '\n';
    const auto column = matrix.column_at(0);
    column.at(1) = 42.0;
    std::cout << "After setting element (0, 1) to 42.0:\n" << matrix << '\n';

    EXPECT_DOUBLE_EQ(matrix.at(0, 1), 42.0);
}

TEST(MatrixAccessRowColumn, RowViewReplacesValuesFromAnotherRow) {
    Matrix matrix{{1, 2, 3}, {4, 5, 6}};
    const auto destination = matrix.row_at(0);
    const auto source = matrix.row_at(1);

    destination.replace(source);

    const Matrix expected{{4, 5, 6}, {4, 5, 6}};
    EXPECT_TRUE(matrix == expected);
}

TEST(MatrixAccessRowColumn, ColumnViewReplacesValuesFromConstColumn) {
    Matrix matrix{{1, 2}, {3, 4}, {5, 6}};
    const Matrix source_matrix{{7}, {8}, {9}};

    matrix.column_at(1).replace(source_matrix.column_at(0));

    const Matrix expected{{1, 7}, {3, 8}, {5, 9}};
    EXPECT_TRUE(matrix == expected);
}

TEST(MatrixAccessRowColumn, ViewReplaceRejectsDifferentSizesWithoutChangingDestination) {
    Matrix matrix{{1, 2}, {3, 4}};
    const Matrix short_row{{5}};

    EXPECT_THROW(matrix.row_at(0).replace(short_row.row_at(0)), std::invalid_argument);
    EXPECT_DOUBLE_EQ(matrix.at(0, 0), 1.0);
    EXPECT_DOUBLE_EQ(matrix.at(1, 0), 2.0);
}

TEST(MatrixAccessRowColumn, RowIteratorVisitsElementsInOrderWithCoordinates) {
    Matrix matrix{{1, 2, 3}, {4, 5, 6}};

    std::cout << "Iterating row 1 by coordinates and reference; doubling every value.\n"
              << "Before:\n" << matrix << '\n';
    for (auto [x, y, value] : matrix.row_at(1)) {
        EXPECT_EQ(y, 1u);
        EXPECT_DOUBLE_EQ(value, matrix.at(x, y));
        value *= 2;
    }

    std::cout << "After:\n" << matrix << '\n';
    const Matrix expected{{1, 2, 3}, {8, 10, 12}};
    EXPECT_TRUE(matrix == expected);
}

TEST(MatrixAccessRowColumn, ColumnIteratorVisitsElementsInOrderWithCoordinates) {
    Matrix matrix{{1, 2, 3}, {4, 5, 6}};

    std::cout << "Iterating column 0 by coordinates and reference; doubling every value.\n"
              << "Before:\n" << matrix << '\n';
    for (auto [x, y, value] : matrix.column_at(0)) {
        EXPECT_EQ(x, 0u);
        EXPECT_DOUBLE_EQ(value, matrix.at(x, y));
        value *= 2;
    }

    std::cout << "After:\n" << matrix << '\n';
    const Matrix expected{{2, 2, 3}, {8, 5, 6}};
    EXPECT_TRUE(matrix == expected);
}

TEST(MatrixAccessRowColumn, ConstRowIteratorVisitsElements) {
    const Matrix matrix{{1, 2, 3}, {4, 5, 6}};

    std::cout << "Iterating row 0 of a const matrix by coordinates and value:\n" << matrix << '\n';
    size_t count = 0;
    for (const auto [x, y, value] : matrix.row_at(0)) {
        EXPECT_EQ(y, 0u);
        EXPECT_DOUBLE_EQ(value, matrix.at(x, y));
        ++count;
    }

    EXPECT_EQ(count, 3u);
}

TEST(MatrixAccessRowColumn, ConstColumnIteratorVisitsElements) {
    const Matrix matrix{{1, 2, 3}, {4, 5, 6}};

    std::cout << "Iterating column 1 of a const matrix by coordinates and value:\n" << matrix << '\n';
    size_t count = 0;
    for (const auto [x, y, value] : matrix.column_at(1)) {
        EXPECT_EQ(x, 1u);
        EXPECT_DOUBLE_EQ(value, matrix.at(x, y));
        ++count;
    }

    EXPECT_EQ(count, 2u);
}

TEST(MatrixAccessRowColumn, ThrowsForOutOfRangeRowOrColumnIndex) {
    Matrix matrix(2, 2);
    const Matrix const_matrix(2, 2);

    std::cout << "Accessing row/column index 2 outside this 2x2 matrix must throw std::out_of_range:\n"
              << matrix << '\n';
    EXPECT_THROW((void)matrix.row_at(2), std::out_of_range);
    EXPECT_THROW((void)matrix.column_at(2), std::out_of_range);
    EXPECT_THROW((void)const_matrix.row_at(2), std::out_of_range);
    EXPECT_THROW((void)const_matrix.column_at(2), std::out_of_range);
}
