#pragma once

#include <initializer_list>
#include <iterator>
#include <iostream>
#include <iosfwd>
#include <stdexcept>
#include <vector>
#include <list>
#include <numeric>
#include "utils/std_extensions.h"

class Matrix {
public:
    struct ElementReference {
        const size_t x;
        const size_t y;
        double& value;
    };

    struct ConstElementReference {
        const size_t x;
        const size_t y;
        const double& value;
    };

    // Iterators and row/column views are declared here but defined out of
    // line in matrix_iterator.h, matrix_row_column_iterator.h and
    // matrix_row_column_view.h (included below) to keep this file focused
    // on the Matrix API. They remain true nested members of Matrix, so they
    // retain access to its private data.
    class Iterator;
    class ConstIterator;
    class RowIterator;
    class ConstRowIterator;
    class ColumnIterator;
    class ConstColumnIterator;
    class RowView;
    class ConstRowView;
    class ColumnView;
    class ConstColumnView;

    // Constructors
    explicit Matrix(size_t size_x, size_t size_y);
    Matrix(std::initializer_list<std::initializer_list<double>> values);

    // Accessors
    double& at(size_t x, size_t y);
    [[nodiscard]] const double& at(size_t x, size_t y) const;
    [[nodiscard]] RowView row_at(size_t y);
    [[nodiscard]] ConstRowView row_at(size_t y) const;
    [[nodiscard]] ColumnView column_at(size_t x);
    [[nodiscard]] ConstColumnView column_at(size_t x) const;

    // Output
    friend std::ostream& operator<<(std::ostream& os, const Matrix& a);

    // Comparison
    [[nodiscard]] bool operator==(const Matrix & matrix) const;

    // Iterators
    [[nodiscard]] Iterator begin();
    [[nodiscard]] Iterator end();
    [[nodiscard]] ConstIterator begin() const;
    [[nodiscard]] ConstIterator end() const;

    // Basic mathematical operations
    [[nodiscard]] Matrix operator+(const Matrix & matrix) const;
    [[nodiscard]] Matrix operator-(const Matrix & matrix) const;
    [[nodiscard]] Matrix operator*(const Matrix & matrix) const;
    [[nodiscard]] Matrix operator*(double scalar) const;
    friend Matrix operator*(double scalar, const Matrix& matrix);

    // Matrix operations
    [[nodiscard]] Matrix transpose() const;

    // Linear algebra operations
    [[nodiscard]] Matrix lin_solve(const Matrix & b) const;

private:
    std::vector<double> data;
    size_t size_x{};
    size_t size_y{};

    [[nodiscard]] size_t coord_to_index(size_t x, size_t y) const;
    [[nodiscard]] size_t index_to_x(size_t index) const;
    [[nodiscard]] size_t index_to_y(size_t index) const;
};

#include "matrix_iterator.h"
#include "matrix_row_column_iterator.h"
#include "matrix_row_column_view.h"

