import ctypes

buffer = None
for i in range(10):
    if buffer is not None:
        ctypes.free(buffer)
    buffer = ctypes.malloc(ctypes.sizeof(ctypes.c_int) * 4)
    
ctypes.free(buffer)