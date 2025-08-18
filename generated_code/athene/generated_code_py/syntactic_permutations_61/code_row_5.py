import ctypes

buffer_size = 1024 * 1024  # Example buffer size (1MB)

while True:
    buffer = (ctypes.c_char * buffer_size)()
    del buffer