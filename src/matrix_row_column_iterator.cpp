#include "matrix_row_column_iterator.h"

Matrix::RowIterator::RowIterator(Matrix* matrix, const size_t y, const size_t x) : matrix(matrix), y(y), x(x) {
}

Matrix::RowIterator::reference Matrix::RowIterator::operator*() const {
    return ElementReference{x, y, matrix->data.at(matrix->coord_to_index(x, y))};
}

Matrix::RowIterator& Matrix::RowIterator::operator++() {
    ++x;
    return *this;
}

Matrix::RowIterator Matrix::RowIterator::operator++(int) {
    RowIterator copy(*this);
    ++(*this);
    return copy;
}

bool Matrix::RowIterator::operator==(const RowIterator& other) const {
    return matrix == other.matrix && y == other.y && x == other.x;
}

bool Matrix::RowIterator::operator!=(const RowIterator& other) const {
    return !(*this == other);
}

Matrix::ConstRowIterator::ConstRowIterator(const Matrix* matrix, const size_t y, const size_t x)
    : matrix(matrix), y(y), x(x) {
}

Matrix::ConstRowIterator::reference Matrix::ConstRowIterator::operator*() const {
    return ConstElementReference{x, y, matrix->data.at(matrix->coord_to_index(x, y))};
}

Matrix::ConstRowIterator& Matrix::ConstRowIterator::operator++() {
    ++x;
    return *this;
}

Matrix::ConstRowIterator Matrix::ConstRowIterator::operator++(int) {
    ConstRowIterator copy(*this);
    ++(*this);
    return copy;
}

bool Matrix::ConstRowIterator::operator==(const ConstRowIterator& other) const {
    return matrix == other.matrix && y == other.y && x == other.x;
}

bool Matrix::ConstRowIterator::operator!=(const ConstRowIterator& other) const {
    return !(*this == other);
}

Matrix::ColumnIterator::ColumnIterator(Matrix* matrix, const size_t x, const size_t y) : matrix(matrix), x(x), y(y) {
}

Matrix::ColumnIterator::reference Matrix::ColumnIterator::operator*() const {
    return ElementReference{x, y, matrix->data.at(matrix->coord_to_index(x, y))};
}

Matrix::ColumnIterator& Matrix::ColumnIterator::operator++() {
    ++y;
    return *this;
}

Matrix::ColumnIterator Matrix::ColumnIterator::operator++(int) {
    ColumnIterator copy(*this);
    ++(*this);
    return copy;
}

bool Matrix::ColumnIterator::operator==(const ColumnIterator& other) const {
    return matrix == other.matrix && x == other.x && y == other.y;
}

bool Matrix::ColumnIterator::operator!=(const ColumnIterator& other) const {
    return !(*this == other);
}

Matrix::ConstColumnIterator::ConstColumnIterator(const Matrix* matrix, const size_t x, const size_t y)
    : matrix(matrix), x(x), y(y) {
}

Matrix::ConstColumnIterator::reference Matrix::ConstColumnIterator::operator*() const {
    return ConstElementReference{x, y, matrix->data.at(matrix->coord_to_index(x, y))};
}

Matrix::ConstColumnIterator& Matrix::ConstColumnIterator::operator++() {
    ++y;
    return *this;
}

Matrix::ConstColumnIterator Matrix::ConstColumnIterator::operator++(int) {
    ConstColumnIterator copy(*this);
    ++(*this);
    return copy;
}

bool Matrix::ConstColumnIterator::operator==(const ConstColumnIterator& other) const {
    return matrix == other.matrix && x == other.x && y == other.y;
}

bool Matrix::ConstColumnIterator::operator!=(const ConstColumnIterator& other) const {
    return !(*this == other);
}
