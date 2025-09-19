import ctypes

chunk1 = (ctypes.c_int * 10)()
chunk2 = (ctypes.c_int * 10)()

ctypes.memmove(chunk2, chunk1, ctypes.sizeof(chunk1))

ctypes.POINTER(ctypes.c_int).from_address(id(chunk1)).contents = None
ctypes.POINTER(ctypes.c_int).from_address(id(chunk2)).contents = None