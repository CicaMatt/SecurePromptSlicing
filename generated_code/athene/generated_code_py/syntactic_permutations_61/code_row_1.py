import ctypes

buffer_size = 1024
buffer = (ctypes.c_char * buffer_size)()

for _ in range(10):
    ctypes.pythonapi.PyMem_Free(buffer)
    buffer = (ctypes.c_char * buffer_size)()