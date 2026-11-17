#include <gtest/gtest.h>

#include <iostream>

#include "matrix/matrix_lib.h"

TEST(MatrixLinSolve, SolvesSimpleLinearSystem) {
    const Matrix A{{1, 2, 1}, {3, 8, 1}, {0, 4, 1}};
    const Matrix b{{2}, {12}, {2}};
    const Matrix expected_x{{2}, {1}, {-2}};

    std::cout << "Solving Ax=b for x where A is:\n" << A
              << "\nand b is:\n" << b << '\n';

    const Matrix computed_x = A.lin_solve(b);

    std::cout << "Computed solution x is:\n" << computed_x << '\n';
    EXPECT_TRUE(computed_x == expected_x);
}

TEST(MatrixIsRowEchelonForm, IsRowEchelonFormTrue) {
    const Matrix matrix{{1, 1, 1}, {0, 1, 1}, {0, 0, 1}};

    std::cout << "A square upper-triangular matrix has leading entries moving right in each row and is in row echelon form:\n"
              << matrix << '\n';
    EXPECT_TRUE(matrix.is_row_echelon_form());
}

TEST(MatrixIsRowEchelonForm, AcceptsSkippedPivotColumnsInRectangularMatrix) {
    const Matrix matrix{{0, 2, 3, 4}, {0, 0, 0, 5}, {0, 0, 0, 0}};

    std::cout << "A rectangular matrix is in row echelon form when pivots move strictly right (column 1 to column 3) and the zero row is last:\n"
              << matrix << '\n';
    EXPECT_TRUE(matrix.is_row_echelon_form());
}

TEST(MatrixIsRowEchelonForm, AcceptsLeadingZeroRowsOnlyAtBottom) {
    const Matrix matrix{{7, 0, 2}, {0, 3, 3}, {0, 0, 0}, {0, 0, 0}};

    std::cout << "A row echelon matrix may have multiple all-zero rows, provided they follow all nonzero rows:\n"
              << matrix << '\n';
    EXPECT_TRUE(matrix.is_row_echelon_form());
}

TEST(MatrixIsRowEchelonForm, AcceptsMatrixWithMoreColumnsThanRows) {
	const Matrix matrix{{5, 0, 2, 4}, {0, 10, 3, 5}, {0, 0, 11, 6}};

	std::cout << "A row echelon matrix may have multiple values in the last row:\n"
			  << matrix << '\n';
	EXPECT_TRUE(matrix.is_row_echelon_form());
}

TEST(MatrixIsRowEchelonForm, AcceptsAllZeroMatrix) {
    const Matrix matrix{{0, 0}, {0, 0}, {0, 0}};

    std::cout << "An all-zero matrix is in row echelon form because every row is zero and there are no pivots out of order:\n"
              << matrix << '\n';
    EXPECT_TRUE(matrix.is_row_echelon_form());
}

TEST(MatrixIsRowEchelonForm, RejectsPivotMovingLeftInLowerRow) {
    const Matrix matrix{{0, 1, 2}, {1, 0, 3}};

    std::cout << "This matrix is not in row echelon form because the lower row's leading entry moves left from column 1 to column 0:\n"
              << matrix << '\n';
    EXPECT_FALSE(matrix.is_row_echelon_form());
}

TEST(MatrixIsRowEchelonForm, RejectsMultipleLeadingEntriesInSameColumn) {
    const Matrix matrix{{1, 2}, {3, 4}};

    std::cout << "This matrix is not in row echelon form because both rows have their leading entry in column 0:\n"
              << matrix << '\n';
    EXPECT_FALSE(matrix.is_row_echelon_form());
}

TEST(MatrixIsRowEchelonForm, RejectsNonzeroRowAfterZeroRow) {
    const Matrix matrix{{1, 0}, {0, 0}, {0, 1}};

    std::cout << "This matrix is not in row echelon form because a nonzero row appears after an all-zero row:\n"
              << matrix << '\n';
    EXPECT_FALSE(matrix.is_row_echelon_form());
}
