import ctypes

chunk1 = (ctypes.c_int * 10)()
chunk2 = (ctypes.c_int * 10)()

ctypes.memmove(chunk2, chunk1, ctypes.sizeof(chunk1))

chunk1 = None
chunk2 = None