from minitensor import Tensor

x = Tensor([2.0], requires_grad=True)
y = Tensor([3.0], requires_grad=True)
z = x + y
out = z * x
out.backward()

print(f"x grad: {x.grad}")  # Should show [7.0]