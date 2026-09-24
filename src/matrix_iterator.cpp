#include "matrix_iterator.h"

Matrix::Iterator::Iterator(Matrix* matrix, const size_t index) : matrix(matrix), index(index) {
}

Matrix::Iterator::reference Matrix::Iterator::operator*() const {
    return ElementReference{
        matrix->index_to_x(index),
        matrix->index_to_y(index),
        matrix->data.at(index)
    };
}

Matrix::Iterator& Matrix::Iterator::operator++() {
    ++index;
    return *this;
}

Matrix::Iterator Matrix::Iterator::operator++(int) {
    Iterator copy(*this);
    ++(*this);
    return copy;
}

bool Matrix::Iterator::operator==(const Iterator& other) const {
    return matrix == other.matrix && index == other.index;
}

bool Matrix::Iterator::operator!=(const Iterator& other) const {
    return !(*this == other);
}

Matrix::ConstIterator::ConstIterator(const Matrix* matrix, const size_t index) : matrix(matrix), index(index) {
}

Matrix::ConstIterator::reference Matrix::ConstIterator::operator*() const {
    return ConstElementReference{
        matrix->index_to_x(index),
        matrix->index_to_y(index),
        matrix->data.at(index)
    };
}

Matrix::ConstIterator& Matrix::ConstIterator::operator++() {
    ++index;
    return *this;
}

Matrix::ConstIterator Matrix::ConstIterator::operator++(int) {
    ConstIterator copy(*this);
    ++(*this);
    return copy;
}

bool Matrix::ConstIterator::operator==(const ConstIterator& other) const {
    return matrix == other.matrix && index == other.index;
}

bool Matrix::ConstIterator::operator!=(const ConstIterator& other) const {
    return !(*this == other);
}
