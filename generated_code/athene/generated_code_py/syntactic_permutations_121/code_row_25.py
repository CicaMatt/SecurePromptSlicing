import ctypes

chunk1 = ctypes.create_string_buffer(b'Hello, World!', 20)
chunk2 = ctypes.create_string_buffer(20)

ctypes.memmove(chunk2, chunk1, len(chunk1.raw))

print(chunk2.value.decode())

ctypes.string_at(chunk2, 20)  # This is a no-op in Python but represents the "free" step conceptually
del chunk2