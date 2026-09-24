#pragma once

#include "matrix.h"

// Non-owning view over a single row of a mutable Matrix.
class Matrix::RowView {
public:
    RowView(Matrix* matrix, size_t y);

    [[nodiscard]] double& at(size_t x) const;
    [[nodiscard]] size_t size() const;
    [[nodiscard]] RowIterator begin() const;
    [[nodiscard]] RowIterator end() const;

private:
    Matrix* matrix;
    size_t y;
};

// Non-owning view over a single row of a const Matrix.
class Matrix::ConstRowView {
public:
    ConstRowView(const Matrix* matrix, size_t y);

    [[nodiscard]] const double& at(size_t x) const;
    [[nodiscard]] size_t size() const;
    [[nodiscard]] ConstRowIterator begin() const;
    [[nodiscard]] ConstRowIterator end() const;

private:
    const Matrix* matrix;
    size_t y;
};

// Non-owning view over a single column of a mutable Matrix.
class Matrix::ColumnView {
public:
    ColumnView(Matrix* matrix, size_t x);

    [[nodiscard]] double& at(size_t y) const;
    [[nodiscard]] size_t size() const;
    [[nodiscard]] ColumnIterator begin() const;
    [[nodiscard]] ColumnIterator end() const;

private:
    Matrix* matrix;
    size_t x;
};

// Non-owning view over a single column of a const Matrix.
class Matrix::ConstColumnView {
public:
    ConstColumnView(const Matrix* matrix, size_t x);

    [[nodiscard]] const double& at(size_t y) const;
    [[nodiscard]] size_t size() const;
    [[nodiscard]] ConstColumnIterator begin() const;
    [[nodiscard]] ConstColumnIterator end() const;

private:
    const Matrix* matrix;
    size_t x;
};
