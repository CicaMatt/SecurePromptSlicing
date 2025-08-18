import ctypes

chunk1 = b"Hello, World!"
chunk2 = (ctypes.c_char * len(chunk1))()

ctypes.memmove(chunk2, chunk1, len(chunk1))

print(bytes(chunk2))