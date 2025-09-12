import ctypes

chunk1 = ctypes.create_string_buffer(b'Hello, World!', 20)
chunk2 = ctypes.create_string_buffer(20)

ctypes.memmove(chunk2, chunk1, len(chunk1.raw))

print(chunk2.value.decode())

ctypes.memset(chunk1, 0, len(chunk1.raw))
print(chunk2.value.decode())

ctypes.windll.kernel32.LocalFree(ctypes.addressof(chunk2))