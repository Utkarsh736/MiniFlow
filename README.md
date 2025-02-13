# MiniFlow

MiniFlow is a minimalistic tensor library implemented in C with Python bindings. It is designed to mimic the core functionality of PyTorch's tensor operations and autograd system, with a focus on simplicity and learning. The library currently supports 1-D tensors, basic operations, and automatic differentiation.

This project is a work in progress and is intended for educational purposes to understand how tensor libraries like PyTorch work under the hood.

## Features

### Current Abilities

* **1-D Tensors**: Support for 1-dimensional tensors with float data type.

* **Basic Operations**:
  * Addition (+)
  * Subtraction (-)
  * Multiplication (*)
  * Broadcasting support for operations between tensors of different sizes.

* **Autograd**:
  * Automatic differentiation for scalar outputs
  * Backpropagation through computational graphs

* **Python Bindings**:
  * Exposes C functionality to Python using ctypes
  * Provides a PyTorch-like interface for tensor operations

## Project Structure

```
miniflow/
├── minitensor.c       # Core C implementation of tensor operations
├── minitensor.h       # Header file for tensor definitions and functions
├── minitensor.py      # Python bindings for the C library
├── test.c             # C test cases
├── test.py            # Python test cases
└── Makefile           # Build and test automation
```

## Getting Started

### Prerequisites

* C compiler (e.g., gcc)
* Python 3.x
* ctypes (included in Python standard library)

### Building the Library

1. Clone the repository:
```bash
git clone https://github.com/yourusername/miniflow.git
cd miniflow
```

2. Build the C library:
```bash
make
```

This will generate `libminitensor.so` (or `libminitensor.dylib` on macOS).

### Running Tests

C Tests:
```bash
make test
```

Python Tests:
```bash
python test.py
```

## Usage

### In C

```c
#include "minitensor.h"

int main() {
    float x_data[] = {2.0};
    float y_data[] = {3.0};
    
    Tensor* x = tensor_create(x_data, 1, 1);  // requires_grad=True
    Tensor* y = tensor_create(y_data, 1, 1);
    Tensor* z = tensor_add(x, y);
    Tensor* out = tensor_mul(z, x);
    
    tensor_backward(out);
    printf("x grad: %.1f\n", x->grad[0]);  // Output: 7.0
    
    tensor_free(x);
    tensor_free(y);
    tensor_free(z);
    tensor_free(out);
    return 0;
}
```

### In Python

```python
from minitensor import Tensor

x = Tensor([2.0], requires_grad=True)
y = Tensor([3.0], requires_grad=True)
z = x + y
out = z * x
out.backward()

print(f"x grad: {x.grad}")  # Output: [7.0]
```

## Next Steps

### Planned Features

* **Multi-Dimensional Tensors**:
  * Support for 2D and ND tensors
  * Implement shape manipulation (reshape, transpose, etc.)

* **Advanced Operations**:
  * Matrix multiplication
  * Reduction operations (sum, mean, etc.)
  * Activation functions (ReLU, sigmoid, etc.)

* **GPU Support**:
  * Integrate CUDA for GPU acceleration

* **Optimizations**:
  * Memory pooling for tensor allocations
  * Efficient broadcasting and operation fusion

* **Extended Autograd**:
  * Support for non-scalar outputs
  * More complex gradient computations (e.g., higher-order derivatives)

* **Python Package**:
  * Package the library for easy installation via pip
  * Add documentation and examples

## Contributing

Contributions are welcome! If you'd like to contribute, please:

1. Fork the repository
2. Create a new branch for your feature or bugfix
3. Submit a pull request with a detailed description of your changes

## License

This project is licensed under the MIT License. See the LICENSE file for details.

## Acknowledgments

* Inspired by PyTorch's design and autograd system
* Built for educational purposes to deepen understanding of tensor libraries and automatic differentiation

## Contact

For questions or feedback, feel free to reach out:

* Email: utkarshtomar736@gmail.com
* GitHub: Utkarsh736
