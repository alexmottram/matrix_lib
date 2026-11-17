#pragma once

#include "matrix.h"
#include "matrix_slice_views.h"
#include "utils/external_deps.h"

// {row index, row view} pair yielded by RowIteratorBase.
template <bool IsConst>
struct Matrix::RowViewReferenceBase {
    size_t row_index;
    RowViewBase<IsConst> row_view;
};

// Forward-iterates over every row of a Matrix, yielding the row index (y)
// alongside a row view. IsConst selects mutable or read-only views.
template <bool IsConst>
class Matrix::RowIteratorBase {
    using MatrixT = std::conditional_t<IsConst, const Matrix, Matrix>;

public:
    using iterator_category = std::input_iterator_tag; // operator* returns by value
    using iterator_concept = std::random_access_iterator_tag;
    using value_type = RowViewReferenceBase<IsConst>;
    using difference_type = std::ptrdiff_t;
    using reference = RowViewReferenceBase<IsConst>;

    RowIteratorBase() = default;

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
    RowIteratorBase& operator--() {
        --row_index;
        return *this;
    }
    RowIteratorBase operator--(int) {
        const RowIteratorBase copy(*this);
        --(*this);
        return copy;
    }
    RowIteratorBase& operator+=(const difference_type n) {
        row_index = static_cast<size_t>(static_cast<difference_type>(row_index) + n);
        return *this;
    }
    RowIteratorBase& operator-=(const difference_type n) { return *this += -n; }
    [[nodiscard]] friend RowIteratorBase operator+(RowIteratorBase it, const difference_type n) { return it += n; }
    [[nodiscard]] friend RowIteratorBase operator+(const difference_type n, RowIteratorBase it) { return it += n; }
    [[nodiscard]] friend RowIteratorBase operator-(RowIteratorBase it, const difference_type n) { return it -= n; }
    [[nodiscard]] friend difference_type operator-(const RowIteratorBase& a, const RowIteratorBase& b) {
        return static_cast<difference_type>(a.row_index) - static_cast<difference_type>(b.row_index);
    }
    [[nodiscard]] reference operator[](const difference_type n) const { return *(*this + n); }
    [[nodiscard]] auto operator<=>(const RowIteratorBase&) const = default;

private:
    friend class RowRangeBase<IsConst>;

    RowIteratorBase(MatrixT* matrix, const size_t row_index) : matrix(matrix), row_index(row_index) {}

    MatrixT* matrix = nullptr;
    size_t row_index = 0;
};

// Range over the rows of a Matrix, returned by Matrix::rows().
template <bool IsConst>
class Matrix::RowRangeBase {
    using MatrixT = std::conditional_t<IsConst, const Matrix, Matrix>;

public:
    [[nodiscard]] RowIteratorBase<IsConst> begin() const { return {matrix_ptr, 0}; }
    [[nodiscard]] RowIteratorBase<IsConst> end() const { return {matrix_ptr, matrix_ptr->size_y}; }

private:
    friend class Matrix;

    explicit RowRangeBase(MatrixT* matrix) : matrix_ptr(matrix) {}

    MatrixT* matrix_ptr;
};

// {column index, column view} pair yielded by ColumnIteratorBase.
template <bool IsConst>
struct Matrix::ColumnViewReferenceBase {
    size_t column_index;
    ColumnViewBase<IsConst> column_view;
};

// Forward-iterates over every column of a Matrix, yielding the column index (x)
// alongside a column view. IsConst selects mutable or read-only views.
template <bool IsConst>
class Matrix::ColumnIteratorBase {
    using MatrixT = std::conditional_t<IsConst, const Matrix, Matrix>;

public:
    using iterator_category = std::input_iterator_tag; // operator* returns by value
    using iterator_concept = std::random_access_iterator_tag;
    using value_type = ColumnViewReferenceBase<IsConst>;
    using difference_type = std::ptrdiff_t;
    using reference = ColumnViewReferenceBase<IsConst>;

    ColumnIteratorBase() = default;

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
    ColumnIteratorBase& operator--() {
        --column_index;
        return *this;
    }
    ColumnIteratorBase operator--(int) {
        const ColumnIteratorBase copy(*this);
        --(*this);
        return copy;
    }
    ColumnIteratorBase& operator+=(const difference_type n) {
        column_index = static_cast<size_t>(static_cast<difference_type>(column_index) + n);
        return *this;
    }
    ColumnIteratorBase& operator-=(const difference_type n) { return *this += -n; }
    [[nodiscard]] friend ColumnIteratorBase operator+(ColumnIteratorBase it, const difference_type n) { return it += n; }
    [[nodiscard]] friend ColumnIteratorBase operator+(const difference_type n, ColumnIteratorBase it) { return it += n; }
    [[nodiscard]] friend ColumnIteratorBase operator-(ColumnIteratorBase it, const difference_type n) { return it -= n; }
    [[nodiscard]] friend difference_type operator-(const ColumnIteratorBase& a, const ColumnIteratorBase& b) {
        return static_cast<difference_type>(a.column_index) - static_cast<difference_type>(b.column_index);
    }
    [[nodiscard]] reference operator[](const difference_type n) const { return *(*this + n); }
    [[nodiscard]] auto operator<=>(const ColumnIteratorBase&) const = default;

private:
    friend class ColumnRangeBase<IsConst>;

    ColumnIteratorBase(MatrixT* matrix, const size_t column_index) : matrix(matrix), column_index(column_index) {}

    MatrixT* matrix = nullptr;
    size_t column_index = 0;
};

// Range over the columns of a Matrix, returned by Matrix::columns().
template <bool IsConst>
class Matrix::ColumnRangeBase {
    using MatrixT = std::conditional_t<IsConst, const Matrix, Matrix>;

public:
    [[nodiscard]] ColumnIteratorBase<IsConst> begin() const { return {matrix_ptr, 0}; }
    [[nodiscard]] ColumnIteratorBase<IsConst> end() const { return {matrix_ptr, matrix_ptr->size_x}; }

private:
    friend class Matrix;

    explicit ColumnRangeBase(MatrixT* matrix) : matrix_ptr(matrix) {}

    MatrixT* matrix_ptr;
};
