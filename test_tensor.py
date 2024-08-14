import tensor_wrapper

# Create a tensor
tensor_ptr = tensor_wrapper.create_tensor(10)
print(f"Tensor created at pointer: {tensor_ptr}")

# View the tensor
new_tensor_ptr = tensor_wrapper.view_tensor(tensor_ptr, 5)
print(f"New tensor created at pointer: {new_tensor_ptr}")

# Free the tensor
tensor_wrapper.free_tensor(tensor_ptr)
print("Tensor freed.")