import ctypes

chunk1 = ctypes.create_string_buffer(b'Hello, World!')
chunk2 = ctypes.create_string_buffer(len(chunk1))

ctypes.memmove(chunk2, chunk1, len(chunk1))
print(chunk2.raw)

ctypes.string_at(chunk2, 0)
print(chunk2.raw)

ctypes.windll.kernel32.LocalFree(ctypes.cast(chunk2, ctypes.c_void_p))
ctypes.windll.kernel32.LocalFree(ctypes.cast(chunk1, ctypes.c_void_p))