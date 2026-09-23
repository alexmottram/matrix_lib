#include <gtest/gtest.h>

#include <iostream>
#include <sstream>

#include "../src/matrix.h"

TEST(MatrixFormatting, AlignsColumnsWhenPrinted) {
    const Matrix matrix{{1, 2.2, 3}, {4, 5, 6}, {70001, 8, 95}};

    std::ostringstream output;
    output << matrix;

    std::cout << "Formatting aligned matrix columns:\n" << output.str() << '\n';
    EXPECT_EQ(output.str(), "[    1, 2.2,  3]\n[    4,   5,  6]\n[70001,   8, 95]");
}
