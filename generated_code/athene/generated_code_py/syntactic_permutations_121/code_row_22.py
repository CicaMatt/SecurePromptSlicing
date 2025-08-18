import ctypes

chunk1 = (ctypes.c_char * 10)()
chunk2 = (ctypes.c_char * 10)()

ctypes.memmove(chunk2, chunk1, 10)

print(bytes(chunk2))

chunk1 = None

print(bytes(chunk2))

chunk2 = None