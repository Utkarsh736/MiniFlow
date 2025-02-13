#include "minitensor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Tensor* tensor_create(const float* data, int size, int requires_grad) {
    Tensor* t = malloc(sizeof(Tensor));
    t->size = size;
    t->data = malloc(size * sizeof(float));
    memcpy(t->data, data, size * sizeof(float));
    
    t->requires_grad = requires_grad;
    t->grad = calloc(size, sizeof(float));
    t->op_type = OP_NONE;
    t->parent0 = t->parent1 = NULL;
    t->visited = 0;
    return t;
}

Tensor* tensor_create_uninitialized(int size) {
    Tensor* t = malloc(sizeof(Tensor));
    t->size = size;
    t->data = malloc(size * sizeof(float));
    t->requires_grad = 0;
    t->grad = calloc(size, sizeof(float));
    t->op_type = OP_NONE;
    t->parent0 = t->parent1 = NULL;
    t->visited = 0;
    return t;
}

void tensor_free(Tensor* t) {
    if (!t) return;
    free(t->data);
    free(t->grad);
    free(t);
}

// Helper for broadcasting
static int broadcast_shapes(int a_size, int b_size) {
    if (a_size == b_size) return a_size;
    if (a_size == 1) return b_size;
    if (b_size == 1) return a_size;
    fprintf(stderr, "Broadcasting failed\n");
    exit(EXIT_FAILURE);
}

Tensor* tensor_add(Tensor* a, Tensor* b) {
    int size = broadcast_shapes(a->size, b->size);
    Tensor* out = tensor_create_uninitialized(size);
    
    for (int i = 0; i < size; i++) {
        float av = a->size == 1 ? a->data[0] : a->data[i];
        float bv = b->size == 1 ? b->data[0] : b->data[i];
        out->data[i] = av + bv;
    }
    
    out->requires_grad = a->requires_grad || b->requires_grad;
    out->op_type = OP_ADD;
    out->parent0 = a;
    out->parent1 = b;
    return out;
}

// Similar implementations for tensor_sub and tensor_mul
// [Include implementations for subtraction and multiplication...]

static void add_backward(Tensor* t) {
    Tensor *a = t->parent0, *b = t->parent1;
    
    if (a->requires_grad) {
        if (a->size == 1) {
            float sum = 0;
            for (int i = 0; i < t->size; i++) sum += t->grad[i];
            a->grad[0] += sum;
        } else {
            for (int i = 0; i < a->size; i++) a->grad[i] += t->grad[i];
        }
    }
    
    if (b->requires_grad) {
        // Similar to a's implementation
    }
}

// Implement backward functions for other operations...

static void build_order(Tensor* t, Tensor** order, int* index) {
    if (!t || t->visited) return;
    t->visited = 1;
    build_order(t->parent0, order, index);
    build_order(t->parent1, order, index);
    order[(*index)++] = t;
}

void tensor_backward(Tensor* t) {
    if (t->size != 1) {
        fprintf(stderr, "Backward requires scalar tensor\n");
        return;
    }

    // Topological sort
    Tensor** order = malloc(1024 * sizeof(Tensor*));
    int index = 0;
    
    build_order(t, order, &index);
    
    // Initialize gradient
    t->grad[0] = 1.0;
    
    // Reverse process
    for (int i = index-1; i >= 0; i--) {
        Tensor* curr = order[i];
        switch (curr->op_type) {
            case OP_ADD: add_backward(curr); break;
            // Handle other operations...
        }
    }
    
    free(order);
}