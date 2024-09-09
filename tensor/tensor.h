#ifndef TENSOR_HPP
#define TENSOR_HPP

#include <vector>
#include <numeric>
#include <type_traits>
#include <iostream>

// Tensor class template for arithmetic types only
template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
class Tensor {
private:
    std::vector<T> data;
    std::vector<size_t> shape;
    size_t total_size = 0;

public:
    Tensor(const std::vector<size_t>& shape) : shape(shape) {
        total_size = std::accumulate(shape.begin(), shape.end(), 1, std::multiplies<size_t>());
        data.resize(total_size);  // Allocate memory for tensor data
    }

    Tensor(std::initializer_list<size_t> shape) : shape(shape) {
        total_size = std::accumulate(shape.begin(), shape.end(), 1, std::multiplies<size_t>());
        data.resize(total_size);  // Allocate memory for tensor data
    }

    // Overloaded operator() to access tensor elements by indices
    T& operator()(const std::vector<size_t>& indices) {
        size_t offset = computeOffset(indices);
        return data[offset];
    }

    // Constant version of the operator()
    const T& operator()(const std::vector<size_t>& indices) const {
        size_t offset = computeOffset(indices);
        return data[offset];
    }

    std::vector<size_t> getShape() const {
        return shape;
    }

    //flat representation (for debugging)
    void print() const {
        for (const auto& val : data) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }

    // Fill tensor with a specific value
    void fill(T value) {
        std::fill(data.begin(), data.end(), value);
    }

private:
    // Compute the offset in the flat vector for the given indices
    size_t computeOffset(const std::vector<size_t>& indices) const {
        if (indices.size() != shape.size()) {
            throw std::invalid_argument("Number of indices must match tensor dimensions.");
        }
        size_t offset = 0;
        size_t stride = 1;
        for (int i = shape.size() - 1; i >= 0; --i) {
            offset += indices[i] * stride;
            stride *= shape[i];
        }
        return offset;
    }
};

#endif // TENSOR_HPP
