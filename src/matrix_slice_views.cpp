#include "matrix_slice_views.h"
#include "utils/external_deps.h"

template <bool IsConst>
Matrix::RowViewBase<IsConst>::RowViewBase(MatrixT* matrix, const size_t y) : matrix(matrix), y(y) {
}

template <bool IsConst>
typename Matrix::RowViewBase<IsConst>::ElementRef Matrix::RowViewBase<IsConst>::at(const size_t x) const {
    return matrix->at(x, y);
}

template <bool IsConst>
size_t Matrix::RowViewBase<IsConst>::size() const {
    return matrix->size_x;
}

template <bool IsConst>
typename Matrix::RowViewBase<IsConst>::Iter Matrix::RowViewBase<IsConst>::begin() const {
    return Iter(matrix, y, 0);
}

template <bool IsConst>
typename Matrix::RowViewBase<IsConst>::Iter Matrix::RowViewBase<IsConst>::end() const {
    return Iter(matrix, y, matrix->size_x);
}

template <bool IsConst>
Matrix Matrix::RowViewBase<IsConst>::copy() const {
    Matrix result(size(), 1);
    for (size_t x = 0; x < size(); ++x) {
        result.at(x, 0) = at(x);
    }
    return result;
}

template <bool IsConst>
template <bool SourceIsConst>
    requires (!IsConst)
void Matrix::RowViewBase<IsConst>::replace(const RowViewBase<SourceIsConst>& source) const {
    if (size() != source.size()) {
        throw std::invalid_argument("Row views must have the same size");
    }

    for (size_t i = 0; i < size(); ++i) {
        at(i) = source.at(i);
    }
}

template <bool IsConst>
std::ostream& operator<<(std::ostream& os, const Matrix::RowViewBase<IsConst>& row) {
    os << "[";
    for (size_t i = 0; i < row.size(); ++i) {
        if (i > 0) {
            os << ", ";
        }
        os << row.at(i);
    }
    os << "]";

    return os;
}

template <bool IsConst>
Matrix::ColumnViewBase<IsConst>::ColumnViewBase(MatrixT* matrix, const size_t x) : matrix(matrix), x(x) {
}

template <bool IsConst>
typename Matrix::ColumnViewBase<IsConst>::ElementRef Matrix::ColumnViewBase<IsConst>::at(const size_t y) const {
    return matrix->at(x, y);
}

template <bool IsConst>
size_t Matrix::ColumnViewBase<IsConst>::size() const {
    return matrix->size_y;
}

template <bool IsConst>
typename Matrix::ColumnViewBase<IsConst>::Iter Matrix::ColumnViewBase<IsConst>::begin() const {
    return Iter(matrix, x, 0);
}

template <bool IsConst>
typename Matrix::ColumnViewBase<IsConst>::Iter Matrix::ColumnViewBase<IsConst>::end() const {
    return Iter(matrix, x, matrix->size_y);
}

template <bool IsConst>
Matrix Matrix::ColumnViewBase<IsConst>::copy() const {
    Matrix result(1, size());
    for (size_t y = 0; y < size(); ++y) {
        result.at(0, y) = at(y);
    }
    return result;
}

template <bool IsConst>
template <bool SourceIsConst>
    requires (!IsConst)
void Matrix::ColumnViewBase<IsConst>::replace(const ColumnViewBase<SourceIsConst>& source) const {
    if (size() != source.size()) {
        throw std::invalid_argument("Column views must have the same size");
    }

    for (size_t i = 0; i < size(); ++i) {
        at(i) = source.at(i);
    }
}

template <bool IsConst>
std::ostream& operator<<(std::ostream& os, const Matrix::ColumnViewBase<IsConst>& column) {
    os << "[";
    for (size_t i = 0; i < column.size(); ++i) {
        if (i > 0) {
            os << ", ";
        }
        os << column.at(i);
    }
    os << "]";

    return os;
}

// Explicit instantiations for the two constness variants actually used
// (RowView/ConstRowView, ColumnView/ConstColumnView), keeping the template
// implementation out of the header. Note replace()'s member template is
// explicitly instantiated below only for mutable destinations.
template class Matrix::RowViewBase<false>;
template class Matrix::RowViewBase<true>;
template class Matrix::ColumnViewBase<false>;
template class Matrix::ColumnViewBase<true>;
template std::ostream& operator<<(std::ostream&, const Matrix::RowViewBase<false>&);
template std::ostream& operator<<(std::ostream&, const Matrix::RowViewBase<true>&);
template std::ostream& operator<<(std::ostream&, const Matrix::ColumnViewBase<false>&);
template std::ostream& operator<<(std::ostream&, const Matrix::ColumnViewBase<true>&);

// Explicit instantiations of replace() for every combination actually used
// by client code (mutable destination, mutable or const source).
template void Matrix::RowViewBase<false>::replace<false>(const RowViewBase<false>&) const;
template void Matrix::RowViewBase<false>::replace<true>(const RowViewBase<true>&) const;
template void Matrix::ColumnViewBase<false>::replace<false>(const ColumnViewBase<false>&) const;
template void Matrix::ColumnViewBase<false>::replace<true>(const ColumnViewBase<true>&) const;
