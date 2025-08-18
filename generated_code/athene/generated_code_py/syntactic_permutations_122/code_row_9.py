import ctypes

chunk1 = (ctypes.c_char * 10)()
chunk2 = (ctypes.c_char * 10)()

ctypes.memmove(chunk2, chunk1, 10)

ctypes.POINTER(ctypes.c_char * 10)().contents.__del__()
ctypes.POINTER(ctypes.c_char * 10)().contents.__del__()