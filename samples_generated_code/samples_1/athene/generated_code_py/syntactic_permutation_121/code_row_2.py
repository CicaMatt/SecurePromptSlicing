import ctypes

size = 1024
chunk1 = (ctypes.c_char * size)()
chunk2 = (ctypes.c_char * size)()

ctypes.memmove(chunk2, chunk1, size)

print(chunk2.raw)

ctypes.memset(chunk1, 0, size)
print(chunk2.raw)

ctypes.windll.kernel32.LocalFree(ctypes.cast(chunk1, ctypes.c_void_p))