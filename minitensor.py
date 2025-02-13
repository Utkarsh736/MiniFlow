import ctypes
import numpy as np

lib = ctypes.CDLL('./libtensor.so')

# Tensor creation
lib.tensor_create.restype = ctypes.c_void_p
lib.tensor_create.argtypes = [
    ctypes.POINTER(ctypes.c_float),
    ctypes.c_int,
    ctypes.c_int
]

# Backward pass
lib.tensor_backward.argtypes = [ctypes.c_void_p]

class Tensor:
    def __init__(self, data, requires_grad=False):
        self.data = np.array(data, dtype=np.float32)
        self.ptr = lib.tensor_create(
            self.data.ctypes.data_as(ctypes.POINTER(ctypes.c_float)),
            self.data.size,
            requires_grad
        )
    
    def backward(self):
        lib.tensor_backward(self.ptr)
    
    def __add__(self, other):
        return _add(self, other)
    
    # Implement other operators...

def _add(a, b):
    result_ptr = lib.tensor_add(a.ptr, b.ptr)
    # Create wrapper for result tensor...