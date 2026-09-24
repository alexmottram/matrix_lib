#include "matrix_row_column_view.h"

Matrix::RowView::RowView(Matrix* matrix, const size_t y) : matrix(matrix), y(y) {
}

double& Matrix::RowView::at(const size_t x) const {
    return matrix->at(x, y);
}

size_t Matrix::RowView::size() const {
    return matrix->size_x;
}

Matrix::RowIterator Matrix::RowView::begin() const {
    return RowIterator(matrix, y, 0);
}

Matrix::RowIterator Matrix::RowView::end() const {
    return RowIterator(matrix, y, matrix->size_x);
}

Matrix::ConstRowView::ConstRowView(const Matrix* matrix, const size_t y) : matrix(matrix), y(y) {
}

const double& Matrix::ConstRowView::at(const size_t x) const {
    return matrix->at(x, y);
}

size_t Matrix::ConstRowView::size() const {
    return matrix->size_x;
}

Matrix::ConstRowIterator Matrix::ConstRowView::begin() const {
    return ConstRowIterator(matrix, y, 0);
}

Matrix::ConstRowIterator Matrix::ConstRowView::end() const {
    return ConstRowIterator(matrix, y, matrix->size_x);
}

Matrix::ColumnView::ColumnView(Matrix* matrix, const size_t x) : matrix(matrix), x(x) {
}

double& Matrix::ColumnView::at(const size_t y) const {
    return matrix->at(x, y);
}

size_t Matrix::ColumnView::size() const {
    return matrix->size_y;
}

Matrix::ColumnIterator Matrix::ColumnView::begin() const {
    return ColumnIterator(matrix, x, 0);
}

Matrix::ColumnIterator Matrix::ColumnView::end() const {
    return ColumnIterator(matrix, x, matrix->size_y);
}

Matrix::ConstColumnView::ConstColumnView(const Matrix* matrix, const size_t x) : matrix(matrix), x(x) {
}

const double& Matrix::ConstColumnView::at(const size_t y) const {
    return matrix->at(x, y);
}

size_t Matrix::ConstColumnView::size() const {
    return matrix->size_y;
}

Matrix::ConstColumnIterator Matrix::ConstColumnView::begin() const {
    return ConstColumnIterator(matrix, x, 0);
}

Matrix::ConstColumnIterator Matrix::ConstColumnView::end() const {
    return ConstColumnIterator(matrix, x, matrix->size_y);
}
