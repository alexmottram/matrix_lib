#pragma once

#include "matrix.h"

#include <iterator>
#include <type_traits>

// {row index, row view} pair yielded by RowIteratorBase.
template <bool IsConst>
struct Matrix::RowViewReferenceBase {
    const size_t row_index;
    RowViewBase<IsConst> row_view;
};

// Forward-iterates over every row of a Matrix, yielding the row index (y)
// alongside a row view. IsConst selects mutable or read-only views.
template <bool IsConst>
class Matrix::RowIteratorBase {
    using MatrixT = std::conditional_t<IsConst, const Matrix, Matrix>;

public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = RowViewBase<IsConst>;
    using difference_type = std::ptrdiff_t;
    using reference = RowViewReferenceBase<IsConst>;

    RowIteratorBase(MatrixT* matrix, const size_t row_index) : matrix(matrix), row_index(row_index) {}

    [[nodiscard]] reference operator*() const { return reference{row_index, matrix->row_at(row_index)}; }
    RowIteratorBase& operator++() {
        ++row_index;
        return *this;
    }
    RowIteratorBase operator++(int) {
        const RowIteratorBase copy(*this);
        ++(*this);
        return copy;
    }
    [[nodiscard]] bool operator==(const RowIteratorBase& other) const {
        return matrix == other.matrix && row_index == other.row_index;
    }
    [[nodiscard]] bool operator!=(const RowIteratorBase& other) const { return !(*this == other); }

private:
    MatrixT* matrix;
    size_t row_index;
};

// begin()/end() provider returned by Matrix::row_iterator().
template <bool IsConst>
class Matrix::RowIteratorConstructorBase {
    using MatrixT = std::conditional_t<IsConst, const Matrix, Matrix>;

public:
    explicit RowIteratorConstructorBase(MatrixT* matrix) : matrix_ptr(matrix) {}
    [[nodiscard]] RowIteratorBase<IsConst> begin() const { return {matrix_ptr, 0}; }
    [[nodiscard]] RowIteratorBase<IsConst> end() const { return {matrix_ptr, matrix_ptr->size_y}; }

private:
    MatrixT* matrix_ptr;
};

// {column index, column view} pair yielded by ColumnIteratorBase.
template <bool IsConst>
struct Matrix::ColumnViewReferenceBase {
    const size_t column_index;
    ColumnViewBase<IsConst> column_view;
};

// Forward-iterates over every column of a Matrix, yielding the column index
// (x) alongside a column view. IsConst selects mutable or read-only views.
template <bool IsConst>
class Matrix::ColumnIteratorBase {
    using MatrixT = std::conditional_t<IsConst, const Matrix, Matrix>;

public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = ColumnViewBase<IsConst>;
    using difference_type = std::ptrdiff_t;
    using reference = ColumnViewReferenceBase<IsConst>;

    ColumnIteratorBase(MatrixT* matrix, const size_t column_index) : matrix(matrix), column_index(column_index) {}

    [[nodiscard]] reference operator*() const { return reference{column_index, matrix->column_at(column_index)}; }
    ColumnIteratorBase& operator++() {
        ++column_index;
        return *this;
    }
    ColumnIteratorBase operator++(int) {
        const ColumnIteratorBase copy(*this);
        ++(*this);
        return copy;
    }
    [[nodiscard]] bool operator==(const ColumnIteratorBase& other) const {
        return matrix == other.matrix && column_index == other.column_index;
    }
    [[nodiscard]] bool operator!=(const ColumnIteratorBase& other) const { return !(*this == other); }

private:
    MatrixT* matrix;
    size_t column_index;
};

// begin()/end() provider returned by Matrix::column_iterator().
template <bool IsConst>
class Matrix::ColumnIteratorConstructorBase {
    using MatrixT = std::conditional_t<IsConst, const Matrix, Matrix>;

public:
    explicit ColumnIteratorConstructorBase(MatrixT* matrix) : matrix_ptr(matrix) {}
    [[nodiscard]] ColumnIteratorBase<IsConst> begin() const { return {matrix_ptr, 0}; }
    [[nodiscard]] ColumnIteratorBase<IsConst> end() const { return {matrix_ptr, matrix_ptr->size_x}; }

private:
    MatrixT* matrix_ptr;
};
