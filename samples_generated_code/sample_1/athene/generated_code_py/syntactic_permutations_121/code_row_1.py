import ctypes

size = 1024
chunk1 = (ctypes.c_char * size)()
chunk2 = (ctypes.c_char * size)()

ctypes.memmove(chunk2, chunk1, size)

print(chunk2.raw)

ctypes.memset(chunk1, 0, size)
del chunk1

print(chunk2.raw)

del chunk2