#pragma once

#ifndef MATRIX_LIB_MATRIX_H
#define MATRIX_LIB_MATRIX_H

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
    // line in matrix_iterator.h, matrix_slice_views.h and
    // matrix_slice_iterators.h (included below) to keep this file focused
    // on the Matrix API. They remain true nested members of Matrix, so they
    // retain access to its private data.
    class Iterator;
    class ConstIterator;

    // RowViewIteratorBase<IsConst> and ColumnViewIteratorBase<IsConst> iterate
    // over the elements of a single row/column view. They are templated on
    // constness so the mutable and read-only iterators share one
    // implementation; RowViewIterator/ConstRowViewIterator (and the column
    // equivalents) are aliases for the two instantiations actually used.
    template <bool IsConst> class RowViewIteratorBase;
    template <bool IsConst> class ColumnViewIteratorBase;
    using RowViewIterator = RowViewIteratorBase<false>;
    using ConstRowViewIterator = RowViewIteratorBase<true>;
    using ColumnViewIterator = ColumnViewIteratorBase<false>;
    using ConstColumnViewIterator = ColumnViewIteratorBase<true>;

    // RowViewBase<IsConst> and ColumnViewBase<IsConst> are likewise templated
    // on constness; RowView/ConstRowView (and the column equivalents) are
    // aliases for the two instantiations actually used.
    template <bool IsConst> class RowViewBase;
    template <bool IsConst> class ColumnViewBase;
    using RowView = RowViewBase<false>;
    using ConstRowView = RowViewBase<true>;
    using ColumnView = ColumnViewBase<false>;
    using ConstColumnView = ColumnViewBase<true>;

    // Constructors
    explicit Matrix(size_t size_x, size_t size_y);
    Matrix(std::initializer_list<std::initializer_list<double>> values);

    // Named factories for single-row / single-column matrices. Named rather
    // than overloaded constructors because two std::initializer_list<double>
    // constructors would be ambiguous to call.
    [[nodiscard]] static Matrix row_vector(std::initializer_list<double> values);
    [[nodiscard]] static Matrix column_vector(std::initializer_list<double> values);

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

    // Row/column ranges (returned by rows()/columns()) yield whole
    // row/column views as {index, view} references. RowRangeBase<IsConst> and
    // RowIteratorBase<IsConst> (and the column equivalents) are templated on
    // constness. Defined in matrix_slice_iterators.h.
    template <bool IsConst> struct RowViewReferenceBase;
    template <bool IsConst> class RowIteratorBase;
    template <bool IsConst> class RowRangeBase;
    template <bool IsConst> struct ColumnViewReferenceBase;
    template <bool IsConst> class ColumnIteratorBase;
    template <bool IsConst> class ColumnRangeBase;
    using RowViewReference = RowViewReferenceBase<false>;
    using ConstRowViewReference = RowViewReferenceBase<true>;
    using RowIterator = RowIteratorBase<false>;
    using ConstRowIterator = RowIteratorBase<true>;
    using RowRange = RowRangeBase<false>;
    using ConstRowRange = RowRangeBase<true>;
    using ColumnViewReference = ColumnViewReferenceBase<false>;
    using ConstColumnViewReference = ColumnViewReferenceBase<true>;
    using ColumnIterator = ColumnIteratorBase<false>;
    using ConstColumnIterator = ColumnIteratorBase<true>;
    using ColumnRange = ColumnRangeBase<false>;
    using ConstColumnRange = ColumnRangeBase<true>;

    // The ranges hold a pointer to the matrix, so calling these on a
    // temporary would dangle; the rvalue overloads are deleted.
    [[nodiscard]] RowRange rows() &;
    [[nodiscard]] ConstRowRange rows() const &;
    void rows() && = delete;
    void rows() const && = delete;
    [[nodiscard]] ColumnRange columns() &;
    [[nodiscard]] ConstColumnRange columns() const &;
    void columns() && = delete;
    void columns() const && = delete;

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
    // TODO -> Check terminology
    [[nodiscard]] bool is_chevron() const;
    [[nodiscard]] Matrix adjusted_matrix() const;

private:
    std::vector<double> data;
    size_t size_x{};
    size_t size_y{};

    [[nodiscard]] size_t coord_to_index(size_t x, size_t y) const;
    [[nodiscard]] size_t index_to_x(size_t index) const;
    [[nodiscard]] size_t index_to_y(size_t index) const;
};

#include "matrix_iterator.h"
#include "matrix_slice_views.h"
#include "matrix_slice_iterators.h"

#endif // MATRIX_LIB_MATRIX_H
