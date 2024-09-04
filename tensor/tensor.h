#pragma once

#include<vector>


class Tensor:

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
