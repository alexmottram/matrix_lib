#pragma once

#include "matrix.h"

// Forward-iterates over a single row of a mutable Matrix, left to right.
class Matrix::RowIterator {
public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = ElementReference;
    using difference_type = std::ptrdiff_t;
    using reference = ElementReference;

    RowIterator(Matrix* matrix, size_t y, size_t x);

    reference operator*() const;
    RowIterator& operator++();
    RowIterator operator++(int);
    bool operator==(const RowIterator& other) const;
    bool operator!=(const RowIterator& other) const;

private:
    Matrix* matrix;
    size_t y;
    size_t x;
};

// Const counterpart of RowIterator.
class Matrix::ConstRowIterator {
public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = ConstElementReference;
    using difference_type = std::ptrdiff_t;
    using reference = ConstElementReference;

    ConstRowIterator(const Matrix* matrix, size_t y, size_t x);

    [[nodiscard]] reference operator*() const;
    ConstRowIterator& operator++();
    ConstRowIterator operator++(int);
    [[nodiscard]] bool operator==(const ConstRowIterator& other) const;
    [[nodiscard]] bool operator!=(const ConstRowIterator& other) const;

private:
    const Matrix* matrix;
    size_t y;
    size_t x;
};

// Forward-iterates over a single column of a mutable Matrix, top to bottom.
class Matrix::ColumnIterator {
public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = ElementReference;
    using difference_type = std::ptrdiff_t;
    using reference = ElementReference;

    ColumnIterator(Matrix* matrix, size_t x, size_t y);

    reference operator*() const;
    ColumnIterator& operator++();
    ColumnIterator operator++(int);
    bool operator==(const ColumnIterator& other) const;
    bool operator!=(const ColumnIterator& other) const;

private:
    Matrix* matrix;
    size_t x;
    size_t y;
};

// Const counterpart of ColumnIterator.
class Matrix::ConstColumnIterator {
public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = ConstElementReference;
    using difference_type = std::ptrdiff_t;
    using reference = ConstElementReference;

    ConstColumnIterator(const Matrix* matrix, size_t x, size_t y);

    [[nodiscard]] reference operator*() const;
    ConstColumnIterator& operator++();
    ConstColumnIterator operator++(int);
    [[nodiscard]] bool operator==(const ConstColumnIterator& other) const;
    [[nodiscard]] bool operator!=(const ConstColumnIterator& other) const;

private:
    const Matrix* matrix;
    size_t x;
    size_t y;
};
