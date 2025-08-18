import ctypes

chunk1 = ctypes.create_string_buffer(10)
chunk2 = ctypes.create_string_buffer(10)

ctypes.memmove(chunk2, chunk1, 10)

print(chunk1.raw)
ctypes.free(chunk1)

print(chunk2.raw)
ctypes.free(chunk2)