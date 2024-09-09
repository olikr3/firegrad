#include "tensor.hpp"
#include <iostream>

int main() {
    Tensor<float> tensor({2, 3});
    tensor.fill(1.5);
    tensor({0, 1}) = 2.5;  // Modify an element

    // Print the contents
    std::cout << "Tensor contents:" << std::endl;
    tensor.print();

    return 0;
}