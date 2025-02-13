#ifndef TENSOR_H
#define TENSOR_H

typedef enum {
    OP_NONE, OP_ADD, OP_SUB, OP_MUL
} OpType;

typedef struct Tensor Tensor;

struct Tensor {
    float* data;
    int size;
    int requires_grad;
    float* grad;
    OpType op_type;
    Tensor* parent0;
    Tensor* parent1;
    int visited;  // For topological sort
};

// Memory management
Tensor* tensor_create(const float* data, int size, int requires_grad);
Tensor* tensor_create_uninitialized(int size);
void tensor_free(Tensor* t);

// Operations
Tensor* tensor_add(Tensor* a, Tensor* b);
Tensor* tensor_sub(Tensor* a, Tensor* b);
Tensor* tensor_mul(Tensor* a, Tensor* b);

// Autograd
void tensor_backward(Tensor* t);
void tensor_zero_grad(Tensor* t);

#endif

