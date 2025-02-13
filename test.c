#include "minitensor.h"
#include <stdio.h>

int main() {
    float x_data[] = {2.0};
    float y_data[] = {3.0};
    
    Tensor* x = tensor_create(x_data, 1, 1);
    Tensor* y = tensor_create(y_data, 1, 1);
    
    Tensor* z = tensor_add(x, y);
    Tensor* out = tensor_mul(z, x);
    
    tensor_backward(out);
    
    printf("x grad: %.1f\n", x->grad[0]);  // Should print 7.0
    
    tensor_free(x);
    tensor_free(y);
    tensor_free(z);
    tensor_free(out);
    
    return 0;
}