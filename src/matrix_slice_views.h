#pragma once

#include "matrix.h"

#include <stdexcept>
#include <type_traits>

// Forward-iterates over a single row of a Matrix, left to right. IsConst
// selects between a mutable iterator (ElementReference, Matrix*) and a
// read-only iterator (ConstElementReference, const Matrix*) sharing one
// implementation. RowIterator/ConstRowIterator are aliases for the two
// instantiations actually used (declared in matrix.h).
template <bool IsConst>
class Matrix::RowViewIteratorBase {
    using MatrixT = std::conditional_t<IsConst, const Matrix, Matrix>;

public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = std::conditional_t<IsConst, ConstElementReference, ElementReference>;
    using difference_type = std::ptrdiff_t;
    using reference = value_type;

    RowViewIteratorBase(MatrixT* matrix, size_t y, size_t x);

    [[nodiscard]] reference operator*() const;
    RowViewIteratorBase& operator++();
    RowViewIteratorBase operator++(int);
    [[nodiscard]] bool operator==(const RowViewIteratorBase& other) const;
    [[nodiscard]] bool operator!=(const RowViewIteratorBase& other) const;

private:
    MatrixT* matrix;
    size_t y;
    size_t x;
};

// Forward-iterates over a single column of a Matrix, top to bottom. IsConst
// selects between a mutable iterator (ElementReference, Matrix*) and a
// read-only iterator (ConstElementReference, const Matrix*) sharing one
// implementation. ColumnIterator/ConstColumnIterator are aliases for the two
// instantiations actually used (declared in matrix.h).
template <bool IsConst>
class Matrix::ColumnViewIteratorBase {
    using MatrixT = std::conditional_t<IsConst, const Matrix, Matrix>;

public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = std::conditional_t<IsConst, ConstElementReference, ElementReference>;
    using difference_type = std::ptrdiff_t;
    using reference = value_type;

    ColumnViewIteratorBase(MatrixT* matrix, size_t x, size_t y);

    [[nodiscard]] reference operator*() const;
    ColumnViewIteratorBase& operator++();
    ColumnViewIteratorBase operator++(int);
    [[nodiscard]] bool operator==(const ColumnViewIteratorBase& other) const;
    [[nodiscard]] bool operator!=(const ColumnViewIteratorBase& other) const;

private:
    MatrixT* matrix;
    size_t x;
    size_t y;
};

// Non-owning view over a single row of a Matrix. IsConst selects between a
// mutable view (double&, RowIterator) and a read-only view (const double&,
// ConstRowIterator) sharing one implementation. RowView/ConstRowView are
// aliases for the two instantiations actually used (declared in matrix.h).
template <bool IsConst>
class Matrix::RowViewBase {
    using MatrixT = std::conditional_t<IsConst, const Matrix, Matrix>;
    using ElementRef = std::conditional_t<IsConst, const double&, double&>;
    using Iter = std::conditional_t<IsConst, ConstRowViewIterator, RowViewIterator>;

public:
    RowViewBase(MatrixT* matrix, size_t y);

    [[nodiscard]] ElementRef at(size_t x) const;
    [[nodiscard]] size_t size() const;
    [[nodiscard]] Iter begin() const;
    [[nodiscard]] Iter end() const;

    // Copies source's values into this row. A read-only view cannot be the
    // destination.
    template <bool SourceIsConst>
        requires (!IsConst)
    void replace(const RowViewBase<SourceIsConst>& source) const;

private:
    MatrixT* matrix;
    size_t y;
};

template <bool IsConst>
std::ostream& operator<<(std::ostream& os, const Matrix::RowViewBase<IsConst>& row);

// Non-owning view over a single column of a Matrix. IsConst selects between a
// mutable view (double&, ColumnIterator) and a read-only view (const double&,
// ConstColumnIterator) sharing one implementation. ColumnView/ConstColumnView
// are aliases for the two instantiations actually used (declared in
// matrix.h).
template <bool IsConst>
class Matrix::ColumnViewBase {
    using MatrixT = std::conditional_t<IsConst, const Matrix, Matrix>;
    using ElementRef = std::conditional_t<IsConst, const double&, double&>;
    using Iter = std::conditional_t<IsConst, ConstColumnViewIterator, ColumnViewIterator>;

public:
    ColumnViewBase(MatrixT* matrix, size_t x);

    [[nodiscard]] ElementRef at(size_t y) const;
    [[nodiscard]] size_t size() const;
    [[nodiscard]] Iter begin() const;
    [[nodiscard]] Iter end() const;

    // Copies source's values into this column. A read-only view cannot be the
    // destination.
    template <bool SourceIsConst>
        requires (!IsConst)
    void replace(const ColumnViewBase<SourceIsConst>& source) const;

private:
    MatrixT* matrix;
    size_t x;
};

template <bool IsConst>
std::ostream& operator<<(std::ostream& os, const Matrix::ColumnViewBase<IsConst>& column);

// The template implementations live in matrix_slice_views.cpp, with
// explicit instantiations for the two constness variants; these `extern
// template` declarations stop other translation units from implicitly
// instantiating (and duplicating) the same specializations.
extern template class Matrix::RowViewBase<false>;
extern template class Matrix::RowViewBase<true>;
extern template class Matrix::ColumnViewBase<false>;
extern template class Matrix::ColumnViewBase<true>;
extern template std::ostream& operator<<(std::ostream&, const Matrix::RowViewBase<false>&);
extern template std::ostream& operator<<(std::ostream&, const Matrix::RowViewBase<true>&);
extern template std::ostream& operator<<(std::ostream&, const Matrix::ColumnViewBase<false>&);
extern template std::ostream& operator<<(std::ostream&, const Matrix::ColumnViewBase<true>&);
extern template class Matrix::RowViewIteratorBase<false>;
extern template class Matrix::RowViewIteratorBase<true>;
extern template class Matrix::ColumnViewIteratorBase<false>;
extern template class Matrix::ColumnViewIteratorBase<true>;
