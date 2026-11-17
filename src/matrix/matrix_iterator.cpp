#include "matrix_iterator.h"

Matrix::Iterator::Iterator(Matrix* matrix, const size_t index) :
    matrix(matrix), index(index) {
}

Matrix::Iterator::reference Matrix::Iterator::operator*() const {
    return ElementReference{
        .x = matrix->index_to_x(index),
        .y = matrix->index_to_y(index),
        .value = matrix->data.at(index)
    };
}

Matrix::Iterator& Matrix::Iterator::operator++() {
    ++index;
    return *this;
}

Matrix::Iterator Matrix::Iterator::operator++(int) {
    const Iterator copy(*this);
    ++(*this);
    return copy;
}

bool Matrix::Iterator::operator==(const Iterator& other) const {
    return matrix == other.matrix && index == other.index;
}

bool Matrix::Iterator::operator!=(const Iterator& other) const {
    return !(*this == other);
}

Matrix::ConstIterator::ConstIterator(const Matrix* matrix, const size_t index) :
    matrix(matrix), index(index) {
}

Matrix::ConstIterator::reference Matrix::ConstIterator::operator*() const {
    return ConstElementReference{
        .x = matrix->index_to_x(index),
        .y = matrix->index_to_y(index),
        .value = matrix->data.at(index)
    };
}

Matrix::ConstIterator& Matrix::ConstIterator::operator++() {
    ++index;
    return *this;
}

Matrix::ConstIterator Matrix::ConstIterator::operator++(int) {
    const ConstIterator copy(*this);
    ++(*this);
    return copy;
}

bool Matrix::ConstIterator::operator==(const ConstIterator& other) const {
    return matrix == other.matrix && index == other.index;
}

bool Matrix::ConstIterator::operator!=(const ConstIterator& other) const {
    return !(*this == other);
}
