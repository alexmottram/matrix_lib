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

Matrix::RowView Matrix::row_at(const size_t y) {
    if (y >= size_y) {
        throw std::out_of_range("Matrix row index out of range");
    }

    return RowView(this, y);
}

Matrix::ConstRowView Matrix::row_at(const size_t y) const {
    if (y >= size_y) {
        throw std::out_of_range("Matrix row index out of range");
    }

    return ConstRowView(this, y);
}

Matrix::ColumnView Matrix::column_at(const size_t x) {
    if (x >= size_x) {
        throw std::out_of_range("Matrix column index out of range");
    }

    return ColumnView(this, x);
}

Matrix::ConstColumnView Matrix::column_at(const size_t x) const {
    if (x >= size_x) {
        throw std::out_of_range("Matrix column index out of range");
    }

    return ConstColumnView(this, x);
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
    return ConstIterator(this, data.size());
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

// TODO complete this
Matrix Matrix::lin_solve(const Matrix &b) const {

    // Throw error if b is not a column vector
    if (b.size_x != 1) {
        throw std::invalid_argument("Matrix b must be a column vector");
    }

    // Throw error if matrix is not square
    if (size_x != size_y) {
        throw std::invalid_argument("Matrix must be square");
    }

    // Throw error if column length doesn't match
    if (size_y != b.size_y) {
        throw std::invalid_argument("Matrix and column vector must have the same number of rows");
    }

    // TODO Create row access operators first
    std::list<size_t> rows_remaining(size_y);
    std::iota(rows_remaining.begin(), rows_remaining.end(), 0);
    std::list<size_t> rows_ordered;

    // for (auto i = 0; i < size_y; ++i) {
    //
    //     while (!rows_remaining.empty()) {
    //         iteration_number++;
    //
    //         for (auto row_it = rows_remaining.begin(); row_it != rows_remaining.end(); ++row_it) {
    //
    //             // If row has a non-zero pivot, move it to the ordered list and break to restart scanning
    //             non_zero_pivot = at()
    //
    //
    //             if (matches(*row_it)) {
    //                 rows_ordered.splice(rows_ordered.end(), rows_remaining, it);
    //
    //                 break; // restart scanning from rows_remaining.begin()
    //             }
    //         }
    //     }
    // }

    return b;
}

bool Matrix::is_echelon() const {
    return false;
}

Matrix Matrix::augmented_matrix() const {
    // Attempts to create an adjusted echelon matrix where each row
    // contains more zero elements than the previous.
    return *this;
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
