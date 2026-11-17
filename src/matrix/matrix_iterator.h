#pragma once

#include "matrix.h"
#include "utils/external_deps.h"

// Forward-iterates over every element of a mutable Matrix in row-major
// order, exposing each element's coordinates alongside a mutable reference.
class Matrix::Iterator {
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

// Const counterpart of Iterator; exposes each element through a read-only
// reference so a const Matrix cannot be mutated while iterating.
class Matrix::ConstIterator {
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
