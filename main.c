#include <stdio.h>
#include "minitensor.h" // Include the header file

int main() {
    // Create a tensor of size 5
    Tensor* tensor = create_tensor(5);

    // Inititalize the tensor data
    for (size_t i = 0; i < tensor->size; i++) {
        tensor->data[i] = (float)i; // Fill with values 0, 1, 2, 3, 4
    }

    // Display original tensor
    printf("Original Tensor: ");
    for (size_t i = 0; i < tensor->size; i++) {
        printf("%f ", tensor->data[i]);
    }
    printf("\n");

    // View the tesnor (reshape to same size)
    Tensor* new_tensor = view_tensor(tensor, 5);

    // Display new tensor
    printf("New Tensor: ");
    for (size_t i = 0; i < new_tensor->size; i++) {
        printf("%f ", new_tensor->data[i]);
    }
    printf("\n");

    // Free the tensors
    free_tensor(tensor);
    free_tensor(new_tensor);

    return 0;
}