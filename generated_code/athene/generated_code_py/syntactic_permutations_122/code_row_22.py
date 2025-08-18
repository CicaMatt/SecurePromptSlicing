import ctypes

chunk1 = (ctypes.c_int * 10)()
chunk2 = (ctypes.c_int * 10)()

ctypes.memmove(chunk2, chunk1, 10 * ctypes.sizeof(ctypes.c_int))

chunk2 = None