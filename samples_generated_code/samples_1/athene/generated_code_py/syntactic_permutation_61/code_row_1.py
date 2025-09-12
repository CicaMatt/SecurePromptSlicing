import ctypes

buffer_size = 1024
buffer = ctypes.create_string_buffer(buffer_size)

for _ in range(10):
    ctypes.pythonapi.PyMem_Free(ctypes.cast(buffer, ctypes.c_void_p))
    buffer = ctypes.create_string_buffer(buffer_size)