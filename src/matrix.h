#pragma once

#include <initializer_list>
#include <iterator>
#include <iostream>
#include <iosfwd>
#include <stdexcept>
#include <vector>
#include <list>
#include <numeric>
#include "utils/std_extensions.h"

class Matrix {
public:
    struct ElementReference {
        const size_t x;
        const size_t y;
        double& value;
    };

    struct ConstElementReference {
        const size_t x;
        const size_t y;
        const double& value;
    };

    class Iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = ElementReference;
        using difference_type = std::ptrdiff_t;
        using reference = ElementReference;

        Iterator(Matrix* matrix, size_t index);

        reference operator*() const;
        Iterator& operator++();
        Iterator operator++(int);
        bool operator==(const Iterator& other) const;
        bool operator!=(const Iterator& other) const;

    private:
        Matrix* matrix;
        size_t index;
    };

    class ConstIterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = ConstElementReference;
        using difference_type = std::ptrdiff_t;
        using reference = ConstElementReference;

        ConstIterator(const Matrix* matrix, size_t index);

        [[nodiscard]] reference operator*() const;
        ConstIterator& operator++();
        ConstIterator operator++(int);
        [[nodiscard]] bool operator==(const ConstIterator& other) const;
        [[nodiscard]] bool operator!=(const ConstIterator& other) const;

    private:
        const Matrix* matrix;
        size_t index;
    };

    explicit Matrix(size_t size_x, size_t size_y);
    Matrix(std::initializer_list<std::initializer_list<double>> values);
    double& at(size_t x, size_t y);
    [[nodiscard]] const double& at(size_t x, size_t y) const;
    friend std::ostream& operator<<(std::ostream& os, const Matrix& a);

    // Comparison
    [[nodiscard]] bool operator==(const Matrix & matrix) const;

    // Iterators
    [[nodiscard]] Iterator begin();
    [[nodiscard]] Iterator end();
    [[nodiscard]] ConstIterator begin() const;
    [[nodiscard]] ConstIterator end() const;

    // Basic mathematical operations
    [[nodiscard]] Matrix operator+(const Matrix & matrix) const;
    [[nodiscard]] Matrix operator-(const Matrix & matrix) const;
    [[nodiscard]] Matrix operator*(const Matrix & matrix) const;
    [[nodiscard]] Matrix operator*(double scalar) const;
    friend [[nodiscard]] Matrix operator*(double scalar, const Matrix& matrix);

    // Matrix operations
    [[nodiscard]] Matrix transpose() const;

    // Linear algebra operations
    [[nodiscard]] Matrix lin_solve(const Matrix & b) const;

private:
    std::vector<double> data;
    size_t size_x{};
    size_t size_y{};

    [[nodiscard]] size_t coord_to_index(size_t x, size_t y) const;
    [[nodiscard]] size_t index_to_x(size_t index) const;
    [[nodiscard]] size_t index_to_y(size_t index) const;
};
