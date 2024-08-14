// stensor -> simple tensor: A basic 1-d implementaion of pytorch tensor in c capable of performing a .view operation

#include <stdio.h>
#include <stdlib.h>
#include "minitensor.h"

// Step 1: Create the Tensor Structure

// typedef struct {
//     float* data; // Pointer to the tensor's data
//     size_t size; // Number of elements in the tensor
// } Tensor;
// ****Imported from header file "minitensor.h"****

// Step 2: Create the Tensor

Tensor* create_tensor(size_t size) {
    Tensor* tensor = (Tensor*)malloc(sizeof(Tensor));
    tensor->data = (float*)malloc(size * sizeof(float));
    tensor->size = size;
    return tensor;
}

// Step 3: Implement the `.view` method

Tensor* view_tensor(Tensor* tensor, size_t new_size) {
    if (new_size != tensor->size) {
        printf("Error: New size must match the original size. \n");
        return NULL;
    }

    // Create a new tensor with the same data
    Tensor* new_tensor = create_tensor(new_size);
    if (new_tensor == NULL) { // {{ edit_2 }}
        printf("Error: Memory allocation failed.\n");
        return NULL;
    }
    for (size_t i = 0; i < new_size; i++) {
        new_tensor->data[i] = tensor->data[i];
    }
    return new_tensor;
}

// Step 4: Free the Tensor Memory

void free_tensor(Tensor* tensor) {
    free(tensor->data);
    free(tensor);
}