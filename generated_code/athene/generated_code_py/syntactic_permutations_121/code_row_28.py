import ctypes

chunk1 = (ctypes.c_char * 10)()
chunk2 = (ctypes.c_char * 10)()

ctypes.memmove(chunk2, chunk1, len(chunk1))
print(ctypes.string_at(chunk2))

ctypes.memset(chunk1, 0, len(chunk1))
print(ctypes.string_at(chunk2))

del chunk1
del chunk2