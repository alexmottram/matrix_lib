#pragma once

#include "matrix.h"

#include <compare>
#include <iterator>
#include <stdexcept>
#include <type_traits>

// Random-access iterator over a single row of a Matrix, left to right. IsConst
// selects between a mutable iterator (ElementReference, Matrix*) and a
// read-only iterator (ConstElementReference, const Matrix*) sharing one
// implementation. RowViewIterator/ConstRowViewIterator are aliases for the two
// instantiations actually used (declared in matrix.h).
template <bool IsConst>
class Matrix::RowViewIteratorBase {
    using MatrixT = std::conditional_t<IsConst, const Matrix, Matrix>;

public:
    using iterator_category = std::input_iterator_tag; // operator* returns by value
    using iterator_concept = std::random_access_iterator_tag;
    using value_type = std::conditional_t<IsConst, ConstElementReference, ElementReference>;
    using difference_type = std::ptrdiff_t;
    using reference = value_type;

    RowViewIteratorBase() = default;

    [[nodiscard]] reference operator*() const { return reference{x, y, matrix->data.at(matrix->coord_to_index(x, y))}; }
    RowViewIteratorBase& operator++() {
        ++x;
        return *this;
    }
    RowViewIteratorBase operator++(int) {
        const RowViewIteratorBase copy(*this);
        ++(*this);
        return copy;
    }
    RowViewIteratorBase& operator--() {
        --x;
        return *this;
    }
    RowViewIteratorBase operator--(int) {
        const RowViewIteratorBase copy(*this);
        --(*this);
        return copy;
    }
    RowViewIteratorBase& operator+=(const difference_type n) {
        x = static_cast<size_t>(static_cast<difference_type>(x) + n);
        return *this;
    }
    RowViewIteratorBase& operator-=(const difference_type n) { return *this += -n; }
    [[nodiscard]] friend RowViewIteratorBase operator+(RowViewIteratorBase it, const difference_type n) { return it += n; }
    [[nodiscard]] friend RowViewIteratorBase operator+(const difference_type n, RowViewIteratorBase it) { return it += n; }
    [[nodiscard]] friend RowViewIteratorBase operator-(RowViewIteratorBase it, const difference_type n) { return it -= n; }
    [[nodiscard]] friend difference_type operator-(const RowViewIteratorBase& a, const RowViewIteratorBase& b) {
        return static_cast<difference_type>(a.x) - static_cast<difference_type>(b.x);
    }
    [[nodiscard]] reference operator[](const difference_type n) const { return *(*this + n); }
    [[nodiscard]] auto operator<=>(const RowViewIteratorBase&) const = default;

private:
    friend class RowViewBase<IsConst>;

    RowViewIteratorBase(MatrixT* matrix, const size_t y, const size_t x) : matrix(matrix), y(y), x(x) {}

    MatrixT* matrix = nullptr;
    size_t y = 0;
    size_t x = 0;
};

// Random-access iterator over a single column of a Matrix, top to bottom. IsConst
// selects between a mutable iterator (ElementReference, Matrix*) and a
// read-only iterator (ConstElementReference, const Matrix*) sharing one
// implementation. ColumnViewIterator/ConstColumnViewIterator are aliases for the two
// instantiations actually used (declared in matrix.h).
template <bool IsConst>
class Matrix::ColumnViewIteratorBase {
    using MatrixT = std::conditional_t<IsConst, const Matrix, Matrix>;

public:
    using iterator_category = std::input_iterator_tag; // operator* returns by value
    using iterator_concept = std::random_access_iterator_tag;
    using value_type = std::conditional_t<IsConst, ConstElementReference, ElementReference>;
    using difference_type = std::ptrdiff_t;
    using reference = value_type;

    ColumnViewIteratorBase() = default;

    [[nodiscard]] reference operator*() const { return reference{x, y, matrix->data.at(matrix->coord_to_index(x, y))}; }
    ColumnViewIteratorBase& operator++() {
        ++y;
        return *this;
    }
    ColumnViewIteratorBase operator++(int) {
        const ColumnViewIteratorBase copy(*this);
        ++(*this);
        return copy;
    }
    ColumnViewIteratorBase& operator--() {
        --y;
        return *this;
    }
    ColumnViewIteratorBase operator--(int) {
        const ColumnViewIteratorBase copy(*this);
        --(*this);
        return copy;
    }
    ColumnViewIteratorBase& operator+=(const difference_type n) {
        y = static_cast<size_t>(static_cast<difference_type>(y) + n);
        return *this;
    }
    ColumnViewIteratorBase& operator-=(const difference_type n) { return *this += -n; }
    [[nodiscard]] friend ColumnViewIteratorBase operator+(ColumnViewIteratorBase it, const difference_type n) { return it += n; }
    [[nodiscard]] friend ColumnViewIteratorBase operator+(const difference_type n, ColumnViewIteratorBase it) { return it += n; }
    [[nodiscard]] friend ColumnViewIteratorBase operator-(ColumnViewIteratorBase it, const difference_type n) { return it -= n; }
    [[nodiscard]] friend difference_type operator-(const ColumnViewIteratorBase& a, const ColumnViewIteratorBase& b) {
        return static_cast<difference_type>(a.y) - static_cast<difference_type>(b.y);
    }
    [[nodiscard]] reference operator[](const difference_type n) const { return *(*this + n); }
    [[nodiscard]] auto operator<=>(const ColumnViewIteratorBase&) const = default;

private:
    friend class ColumnViewBase<IsConst>;

    ColumnViewIteratorBase(MatrixT* matrix, const size_t x, const size_t y) : matrix(matrix), x(x), y(y) {}

    MatrixT* matrix = nullptr;
    size_t x = 0;
    size_t y = 0;
};

// Non-owning view over a single row of a Matrix. IsConst selects between a
// mutable view (double&, RowViewIterator) and a read-only view (const double&,
// ConstRowViewIterator) sharing one implementation. RowView/ConstRowView are
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
// mutable view (double&, ColumnViewIterator) and a read-only view (const double&,
// ConstColumnViewIterator) sharing one implementation. ColumnView/ConstColumnView
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
