#ifndef TENSOR_H
#define TENSOR_H

#include<vector>


class Tensor {

private:
    std::vector<float> data;
    std::vector<size_t> shape;
    size_t total_size;

    // required for index based access of the flattened data
    size_t compute_offset(const std::vector<size_t> &indices) const {
        size_t offset = 0;
        size_t stride = 1;
        for (int i = shape.size() - 1; i >= 0; --i){
            offset+= indices[i] * stride;
            stride *= shape[i]
        }
        return offset;
    }

public:
    Tensor(const std::vector<size_t> shape) : shape(shape) {
        total_size = std::accumulate(shape.begin(), shape.end(), 1,
        std::multiplies<size_t>());
        data.resize(total_size);
    }

    float& operator()(const std::vector<size_t>& indices) {
        size_t offset = compute_offset(indices);
        return data[offset];
    }

    const float& operator()(const std::vector<size_t>& indices) const {
        size_t offset = compute_offset(indices);
        return data[offset];
    }

    const std::vector<size_t>& getShape() const {
        return shape;
    }

    size_t size() const {
        return total_size;
    }

    Tensor operator+(const Tensor& other) const {
        assert(shape == other.shape);
        Tensor result_Tensor(shape);
        for (size_t i = 0; i < total_size; i++) {
            result_Tensor.data[i] = data[i] + other.data[i];
        }
        return result_Tensor;
    }

    Tensor operator-(const Tensor& other) const {
        assert(shape == other.shape);
        Tensor result_Tensor(shape);
        for (size_t i = 0; i < total_size; i++){
            result_Tensor[i] = data[i] - other.data[i];
        }
        return result_Tensor;
    }

    //not implemented
    Tensor operator*(const Tensor& other) const {
        Tensor result_Tensor(shape);
        return result_Tensor
    }

}
