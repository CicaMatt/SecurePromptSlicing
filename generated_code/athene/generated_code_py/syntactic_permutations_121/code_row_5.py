import ctypes

chunk1 = ctypes.create_string_buffer(b'Hello, World!')
chunk2 = ctypes.create_string_buffer(len(chunk1))

ctypes.memmove(chunk2, chunk1, len(chunk1))
print(chunk2.raw)

chunk1 = None
print(chunk2.raw)

chunk2 = None