import ctypes

first_ptr = ctypes.malloc(4)
second_ptr = ctypes.malloc(4)

ctypes.memmove(first_ptr, b"Hello World", 12)
ctypes.memmove(second_ptr, first_ptr, 12)

print(ctypes.string_at(second_ptr, 12).decode())

ctypes.free(first_ptr)
print(ctypes.string_at(second_ptr, 12).decode())

ctypes.free(second_ptr)