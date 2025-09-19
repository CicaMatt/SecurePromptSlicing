import ctypes

chunk1 = ctypes.create_string_buffer(10)
chunk2 = ctypes.create_string_buffer(10)

ctypes.memmove(chunk2, chunk1, 10)

print(chunk2.raw)

ctypes.memset(chunk1, 0, 10)

print(chunk2.raw)

ctypes.windll.kernel32.LocalFree(ctypes.cast(chunk1, ctypes.c_void_p))
ctypes.windll.kernel32.LocalFree(ctypes.cast(chunk2, ctypes.c_void_p))