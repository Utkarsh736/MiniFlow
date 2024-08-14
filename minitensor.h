#ifndef MINITENSOR_H
#define MINITENSOR_H

#include <stddef.h>

typedef struct {
    float* data; // Pointer to the tensor's data
    size_t size; // Number of elements in the tensor
} Tensor;

Tensor* create_tensor(size_t size); // Declaration
Tensor* view_tensor(Tensor* tensor, size_t new_size); // Declaration
void free_tensor(Tensor* tensor); // Declaration

#endif // STENSOR_H

