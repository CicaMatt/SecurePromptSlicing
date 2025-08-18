import ctypes

size = 1024
chunk1 = (ctypes.c_char * size)()
chunk2 = (ctypes.c_char * size)()

ctypes.memmove(chunk2, chunk1, size)

chunk1 = None
chunk2 = None