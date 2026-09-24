#include <gtest/gtest.h>

#include <iostream>

#include "../src/matrix.h"

TEST(MatrixLinearSolver, SolvesSimpleLinearSystem) {
    const Matrix A{{1, 2, 1}, {3, 8, 1}, {0, 4, 1}};
    const Matrix b{{2}, {12}, {2}};
    const Matrix expected_x{{2}, {1}, {-2}};

    std::cout << "Solving Ax=b for x where A is:\n" << A
              << "\nand b is:\n" << b << '\n';

    const Matrix computed_x = A.lin_solve(b);

    std::cout << "Computed solution x is:\n" << computed_x << '\n';
    EXPECT_TRUE(computed_x == expected_x);
}
