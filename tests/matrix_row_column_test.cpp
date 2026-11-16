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

template <typename Matrix>
concept CanMatrixRowSwap = requires(Matrix& matrix) {
    matrix.swap_rows(0,1);
};

template <typename Matrix>
concept CanMatrixColumnSwap = requires(Matrix& matrix) {
    matrix.swap_columns(0,1);
};

// static_assert is a valid statement inside a TEST body, so these compile-time
// checks get a named entry in the gtest output instead of being invisible
// file-scope code. A violation still fails the build rather than the test run.
TEST(MatrixAccessRowColumn, RowColumnViewsExposeConstCorrectElementReferences) {
    std::cout << "Verifying row and column views preserve constness: const matrices yield const double references and mutable matrices yield double references.\n";
    // A const Matrix only ever exposes read-only row/column views (const
    // double&), so its elements cannot be mutated.
    static_assert(std::is_same_v<decltype(std::declval<const Matrix&>().row_at(0).at(0)), const double&>);
    static_assert(std::is_same_v<decltype(std::declval<const Matrix&>().column_at(0).at(0)), const double&>);
    static_assert(std::is_same_v<decltype(std::declval<Matrix&>().row_at(0).at(0)), double&>);
    static_assert(std::is_same_v<decltype(std::declval<Matrix&>().column_at(0).at(0)), double&>);
}

TEST(MatrixAccessRowColumn, ReplaceIsOnlyAvailableOnMutableMatrixRowViews) {
    std::cout << "Verifying row replace() is available on mutable destination views, including const sources, but unavailable on const destinations.\n";
    static_assert(CanReplaceMatrixRow<Matrix, Matrix>);
    static_assert(CanReplaceMatrixRow<Matrix, const Matrix>);
    static_assert(!CanReplaceMatrixRow<const Matrix, Matrix>);
    static_assert(!CanReplaceMatrixRow<const Matrix, const Matrix>);
}

TEST(MatrixAccessRowColumn, ReplaceIsOnlyAvailableOnMutableMatrixColumnViews) {
    std::cout << "Verifying column replace() is available on mutable destination views, including const sources, but unavailable on const destinations.\n";
    static_assert(CanReplaceMatrixColumn<Matrix, Matrix>);
    static_assert(CanReplaceMatrixColumn<Matrix, const Matrix>);
    static_assert(!CanReplaceMatrixColumn<const Matrix, Matrix>);
    static_assert(!CanReplaceMatrixColumn<const Matrix, const Matrix>);
}

TEST(MatrixAccessRowColumn, RowSwapOnlyAvailableForMutableMatrix) {
    std::cout << "Verifying swap_rows is available on mutable matrices only and unavailable on const destinations.\n";
    static_assert(CanMatrixRowSwap<Matrix>);
    static_assert(!CanMatrixRowSwap<const Matrix>);
}

TEST(MatrixAccessRowColumn, ColumnSwapOnlyAvailableForMutableMatrix) {
    std::cout << "Verifying swap_columns is available on mutable matrices only and unavailable on const destinations.\n";
    static_assert(CanMatrixColumnSwap<Matrix>);
    static_assert(!CanMatrixColumnSwap<const Matrix>);
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
    std::cout << "Column 2, from top to bottom: " << column.at(0) << ", " << column.at(1) << '\n';

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

    std::cout << "Replacing row 0 with row 1:\nBefore:\n" << matrix << '\n';
    destination.replace(source);

    const Matrix expected{{4, 5, 6}, {4, 5, 6}};
    std::cout << "After replacement:\n" << matrix << '\n';
    EXPECT_TRUE(matrix == expected);
}

TEST(MatrixAccessRowColumn, ColumnViewReplacesValuesFromConstColumn) {
    Matrix matrix{{1, 2}, {3, 4}, {5, 6}};
    const Matrix source_matrix{{7}, {8}, {9}};

    std::cout << "Replacing column 1 with values from a const source column:\nDestination before:\n" << matrix
              << "\nSource:\n" << source_matrix << '\n';
    matrix.column_at(1).replace(source_matrix.column_at(0));

    const Matrix expected{{1, 7}, {3, 8}, {5, 9}};
    std::cout << "Destination after replacement:\n" << matrix << '\n';
    EXPECT_TRUE(matrix == expected);
}

TEST(MatrixAccessRowColumn, ViewReplaceRejectsDifferentSizesWithoutChangingDestination) {
    Matrix matrix{{1, 2}, {3, 4}};
    const Matrix short_row{{5}};

    std::cout << "Replacing a two-element row with a one-element row must throw std::invalid_argument and preserve the destination:\n"
              << matrix << '\n';
    EXPECT_THROW(matrix.row_at(0).replace(short_row.row_at(0)), std::invalid_argument);
    EXPECT_DOUBLE_EQ(matrix.at(0, 0), 1.0);
    EXPECT_DOUBLE_EQ(matrix.at(1, 0), 2.0);
}

TEST(MatrixAccessRowColumn, RowViewCopyReturnsIndependentRowMatrix) {
    Matrix matrix{{1, 2, 3}, {4, 5, 6}};
    const Matrix row_copy = matrix.row_at(1).copy();
    const Matrix expected_row{{4, 5, 6}};

    matrix.at(0, 1) = 40;

    std::cout << "Copying row 1 should produce an independent 1x3 matrix; changing the source afterward does not change the copy.\n"
              << "Copied row:\n" << row_copy << "\nChanged source:\n" << matrix << '\n';
    EXPECT_EQ(row_copy, expected_row);
}

TEST(MatrixAccessRowColumn, ConstColumnViewCopyReturnsIndependentColumnMatrix) {
    const Matrix matrix{{1, 2, 3}, {4, 5, 6}};
    const Matrix column_copy = matrix.column_at(1).copy();
    const Matrix expected_column{{2}, {5}};

    std::cout << "Copying column 1 from a const matrix should produce an independent 2x1 matrix:\n" << column_copy << '\n';
    EXPECT_EQ(column_copy, expected_column);
}

TEST(MatrixAccessRowColumn, RowViewConvertsToVectorInLeftToRightOrder) {
    const Matrix matrix{{1, 2, 3}, {4, 5, 6}};

    std::cout << "Converting row 1 to a vector should preserve left-to-right order [4, 5, 6].\n";
    EXPECT_EQ(matrix.row_at(1).to_vector(), (std::vector<double>{4, 5, 6}));
}

TEST(MatrixAccessRowColumn, ColumnViewConvertsToVectorInTopToBottomOrder) {
    Matrix matrix{{1, 2, 3}, {4, 5, 6}};

    std::cout << "Converting column 1 to a vector should preserve top-to-bottom order [2, 5].\n";
    EXPECT_EQ(matrix.column_at(1).to_vector(), (std::vector<double>{2, 5}));
}

TEST(MatrixAccessRowColumn, RowIteratorVisitsElementsInOrderWithCoordinates) {
    Matrix matrix{{1, 2, 3}, {4, 5, 6}};

    std::cout << "Iterating row 1 by coordinates and reference; doubling every value.\n"
              << "Before:\n" << matrix << '\n';
    for (auto [x, y, value] : matrix.row_at(1)) {
        EXPECT_EQ(y, 1u);
        EXPECT_DOUBLE_EQ(value, matrix.at(x, y));
        std::cout << "Doubling row value " << value << " at (" << x << ", " << y << ") to " << value * 2 << ".\n";
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
        std::cout << "Doubling column value " << value << " at (" << x << ", " << y << ") to " << value * 2 << ".\n";
        value *= 2;
    }

    std::cout << "After:\n" << matrix << '\n';
    const Matrix expected{{2, 2, 3}, {8, 5, 6}};
    EXPECT_TRUE(matrix == expected);
}

TEST(MatrixAccessRowColumn, ConstRowIteratorVisitsElements) {
    const Matrix matrix{{1, 2, 3}, {4, 5, 6}};

    std::cout << "Iterating row 0 of a const matrix by coordinates and value:\n" << matrix << '\n';
    std::cout << "The iterator should visit three elements and each coordinate should identify its value.\n";
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
    std::cout << "The iterator should visit two elements and each coordinate should identify its value.\n";
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

TEST(MatrixAccessRowColumn, TemporaryRowAndColumnAccessReturnOwningMatrices) {
    const Matrix row = Matrix{{1, 2, 3}, {4, 5, 6}}.row_at(1);
    const Matrix column = Matrix{{1, 2, 3}, {4, 5, 6}}.column_at(1);
    const Matrix expected_row{{4, 5, 6}};
    const Matrix expected_column{{2}, {5}};

    std::cout << "Accessing a row or column on a temporary matrix returns an owning matrix that remains usable afterward.\n"
              << "Owned row:\n" << row << "\nOwned column:\n" << column << '\n';
    EXPECT_EQ(row.row_count(), 1u);
    EXPECT_EQ(row.column_count(), 3u);
    EXPECT_EQ(row, expected_row);
    EXPECT_EQ(column.row_count(), 2u);
    EXPECT_EQ(column.column_count(), 1u);
    EXPECT_EQ(column, expected_column);
}


TEST(MatrixAccessRowColumn, RowSwapSwapsTwoRowsCorrectly) {
    Matrix matrix{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    const Matrix expected_matrix{{1, 2, 3}, {7, 8, 9}, {4, 5, 6}};

    std::cout << "Swaping rows 1 and 2 in matrix:\n" << matrix << '\n';
    matrix.swap_rows(1, 2);
    std::cout << "Matrix after row swap:\n" << matrix << '\n';
    EXPECT_EQ(matrix, expected_matrix);
}

TEST(MatrixAccessRowColumn, RowSwapWithSameRowLeavesMatrixUnchanged) {
    Matrix matrix{{1, 2, 3}, {4, 5, 6}};
    const Matrix expected_matrix{{1, 2, 3}, {4, 5, 6}};

    std::cout << "Swapping row 1 with itself should be a no-op. Matrix:\n" << matrix << '\n';
    matrix.swap_rows(1, 1);
    std::cout << "Matrix after swap_rows(1, 1):\n" << matrix << '\n';
    EXPECT_EQ(matrix, expected_matrix);
}

TEST(MatrixAccessRowColumn, RowSwapThrowsOnOutOfRangeIndexAndLeavesMatrixUnchanged) {
    Matrix matrix{{1, 2}, {3, 4}};
    const Matrix expected_matrix{{1, 2}, {3, 4}};

    std::cout << "swap_rows(0, 2) and swap_rows(2, 0) on a 2-row matrix must throw std::out_of_range without modifying:\n" << matrix << '\n';
    EXPECT_THROW(matrix.swap_rows(0, 2), std::out_of_range);
    EXPECT_THROW(matrix.swap_rows(2, 0), std::out_of_range);
    EXPECT_EQ(matrix, expected_matrix);
}

TEST(MatrixAccessRowColumn, ColumnSwapSwapsTwoColumnsCorrectly) {
    Matrix matrix{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    const Matrix expected_matrix{{1, 3, 2}, {4, 6, 5}, {7, 9, 8}};

    std::cout << "Swapping columns 1 and 2 in matrix:\n" << matrix << '\n';
    matrix.swap_columns(1, 2);
    std::cout << "Matrix after column swap:\n" << matrix << '\n';
    EXPECT_EQ(matrix, expected_matrix);
}

TEST(MatrixAccessRowColumn, ColumnSwapWithSameColumnLeavesMatrixUnchanged) {
    Matrix matrix{{1, 2, 3}, {4, 5, 6}};
    const Matrix expected_matrix{{1, 2, 3}, {4, 5, 6}};

    std::cout << "Swapping column 1 with itself should be a no-op. Matrix:\n" << matrix << '\n';
    matrix.swap_columns(1, 1);
    std::cout << "Matrix after swap_columns(1, 1):\n" << matrix << '\n';
    EXPECT_EQ(matrix, expected_matrix);
}

TEST(MatrixAccessRowColumn, ColumnSwapThrowsOnOutOfRangeIndexAndLeavesMatrixUnchanged) {
    Matrix matrix{{1, 2}, {3, 4}};
    const Matrix expected_matrix{{1, 2}, {3, 4}};

    std::cout << "swap_columns(0, 2) and swap_columns(2, 0) on a 2-column matrix must throw std::out_of_range without modifying:\n" << matrix << '\n';
    EXPECT_THROW(matrix.swap_columns(0, 2), std::out_of_range);
    EXPECT_THROW(matrix.swap_columns(2, 0), std::out_of_range);
    EXPECT_EQ(matrix, expected_matrix);
}