#include "matrix_lib.h"

#include "utils/external_deps.h"

namespace {
size_t checked_element_count(const size_t size_x, const size_t size_y) {
    if (size_x != 0 && size_y > std::numeric_limits<size_t>::max() / size_x) {
        throw std::length_error("Matrix dimensions exceed the maximum element count");
    }
    return size_x * size_y;
}
}

Matrix::Matrix(const size_t size_x, const size_t size_y)
    : data(checked_element_count(size_x, size_y), 0.0), size_x(size_x), size_y(size_y) {
}

Matrix::Matrix(const std::initializer_list<std::initializer_list<double>> values)
    : size_y(values.size()) {
    if (values.size() != 0) {
        size_x = values.begin()->size();
    }

    data.reserve(checked_element_count(size_x, size_y));

    for (const auto& row : values) {
        if (row.size() != size_x) {
            throw std::invalid_argument("matrix rows must all have the same length");
        }

        data.insert(data.end(), row.begin(), row.end());
    }
}

Matrix Matrix::row_vector(const std::initializer_list<double> values) {
    Matrix result(values.size(), 1);

    size_t x = 0;
    for (const double value : values) {
        result.at(x++, 0) = value;
    }

    return result;
}

Matrix Matrix::column_vector(const std::initializer_list<double> values) {
    Matrix result(1, values.size());

    size_t y = 0;
    for (const double value : values) {
        result.at(0, y++) = value;
    }

    return result;
}

double& Matrix::at(const size_t x, const size_t y) {
    return data.at(coord_to_index(x, y));
}

const double& Matrix::at(const size_t x, const size_t y) const {
    return data.at(coord_to_index(x, y));
}

size_t Matrix::row_count() const noexcept {
    return size_y;
}

size_t Matrix::column_count() const noexcept {
    return size_x;
}

Matrix::RowView Matrix::row_at(const size_t y) & {
    if (y >= size_y) {
        throw std::out_of_range("Matrix row index out of range");
    }

    return {this, y};
}

Matrix::ConstRowView Matrix::row_at(const size_t y) const & {
    if (y >= size_y) {
        throw std::out_of_range("Matrix row index out of range");
    }

    return {this, y};
}

Matrix Matrix::row_at(const size_t y) && {
    return static_cast<const Matrix&&>(*this).row_at(y);
}

Matrix Matrix::row_at(const size_t y) const && {
    return static_cast<const Matrix&>(*this).row_at(y).copy();
}

Matrix::ColumnView Matrix::column_at(const size_t x) & {
    if (x >= size_x) {
        throw std::out_of_range("Matrix column index out of range");
    }

    return {this, x};
}

Matrix::ConstColumnView Matrix::column_at(const size_t x) const & {
    if (x >= size_x) {
        throw std::out_of_range("Matrix column index out of range");
    }

    return {this, x};
}

Matrix Matrix::column_at(const size_t x) && {
    return static_cast<const Matrix&&>(*this).column_at(x);
}

Matrix Matrix::column_at(const size_t x) const && {
    return static_cast<const Matrix&>(*this).column_at(x).copy();
}

void Matrix::swap_rows(const size_t row1, const size_t row2) {
    if (row1 >= size_y) {
        throw std::out_of_range("Matrix row index row 1 out of range");
    }
    if (row2 >= size_y) {
        throw std::out_of_range("Matrix row index row 2 out of range");
    }
    if (row1 == row2) {
        return;
    }
    // Both rows are written, so swap in place: no temporary matrix or views.
    for (size_t x = 0; x < size_x; ++x) {
        std::swap(at(x, row1), at(x, row2));
    }
}

void Matrix::swap_columns(const size_t column1, const size_t column2) {
    if (column1 >= size_x) {
        throw std::out_of_range("Matrix column index column 1 out of range");
    }
    if (column2 >= size_x) {
        throw std::out_of_range("Matrix column index column 2 out of range");
    }
    if (column1 == column2) {
        return;
    }
    for (size_t y = 0; y < size_y; ++y) {
        std::swap(at(column1, y), at(column2, y));
    }
}

bool Matrix::operator==(const Matrix &matrix) const {
    if (size_x != matrix.size_x || size_y != matrix.size_y) {
        return false;
    }

    for (const auto [x, y, value] : *this) {
        if (value != matrix.at(x, y)) {
            return false;
        }
    }

    return true;
}

Matrix::Iterator Matrix::begin() {
    return {this, 0};
}

Matrix::Iterator Matrix::end() {
    return {this, data.size()};
}

Matrix::ConstIterator Matrix::begin() const {
    return {this, 0};
}

Matrix::ConstIterator Matrix::end() const {
    return {this, data.size()};
}

Matrix::RowRange Matrix::rows() & {
    return RowRange(this);
}

Matrix::ConstRowRange Matrix::rows() const & {
    return ConstRowRange(this);
}

Matrix::ColumnRange Matrix::columns() & {
    return ColumnRange(this);
}

Matrix::ConstColumnRange Matrix::columns() const & {
    return ConstColumnRange(this);
}

Matrix Matrix::operator+(const Matrix &matrix) const {
    if (size_x != matrix.size_x || size_y != matrix.size_y) {
        throw std::invalid_argument("Matrix dimensions must match for addition");
    }

    Matrix result(size_x, size_y);

    for (const auto [x, y, value] : *this) {
        result.at(x, y) = value + matrix.at(x, y);
    }

    return result;
}

Matrix Matrix::operator-(const Matrix &matrix) const {
    if (size_x != matrix.size_x || size_y != matrix.size_y) {
        throw std::invalid_argument("Matrix dimensions must match for subtraction");
    }

    Matrix result(size_x, size_y);

    for (const auto [x, y, value] : *this) {
        result.at(x, y) = value - matrix.at(x, y);
    }

    return result;
}

Matrix Matrix::operator*(const Matrix &matrix) const {
    if (size_x != matrix.size_y) {
        throw std::invalid_argument("Matrix dimensions must match for multiplication");
    }

    Matrix result(matrix.size_x, size_y);

    for (size_t y = 0; y < size_y; ++y) {
        for (size_t x = 0; x < matrix.size_x; ++x) {
            double sum = 0.0;
            for (size_t k = 0; k < size_x; ++k) {
                sum += at(k, y) * matrix.at(x, k);
            }
            result.at(x, y) = sum;
        }
    }

    return result;
}

Matrix Matrix::operator*(const double scalar) const {
    Matrix result(size_x, size_y);

    for (const auto [x, y, value] : *this) {
        result.at(x, y) = value * scalar;
    }

    return result;
}

Matrix Matrix::transpose() const {
    Matrix result(size_y, size_x);

    for (const auto [x, y, value] : *this) {
        result.at(y, x) = value;
    }

    return result;
}

bool Matrix::is_square() const
{
    return size_x == size_y;
}

size_t Matrix::coord_to_index(const size_t x, const size_t y) const {
    if (x >= size_x || y >= size_y) {
        throw std::out_of_range("Matrix coordinates out of range");
    }

    return y * size_x + x;
}

size_t Matrix::index_to_x(const size_t index) const {
    return index % size_x;
}

size_t Matrix::index_to_y(const size_t index) const {
    return index / size_x;
}

std::ostream& operator<<(std::ostream& os, const Matrix& a) {
    std::vector<size_t> column_widths(a.size_x, 0);

    for (size_t col = 0; col < a.size_x; ++col) {
        for (size_t row = 0; row < a.size_y; ++row) {
            std::ostringstream cell_stream;
            cell_stream << a.at(col, row);
            if (
                const size_t cell_width = cell_stream.str().size();
                cell_width > column_widths.at(col)
                ) {
                column_widths.at(col) = cell_width;
            }
        }
    }

    for (size_t row = 0; row < a.size_y; ++row) {
        os << "[";
        for (size_t col = 0; col < a.size_x; ++col) {
            if (col > 0) {
                os << ", ";
            }
            os << std::setw(static_cast<int>(column_widths.at(col)))
               << a.at(col, row);
        }
        os << "]";
        if (row + 1 < a.size_y) {
            os << '\n';
        }
    }

    return os;
}

Matrix operator*(const double scalar, const Matrix &matrix) {
    return matrix * scalar;
}
