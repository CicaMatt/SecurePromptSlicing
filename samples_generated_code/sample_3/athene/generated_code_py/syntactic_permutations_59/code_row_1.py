import ctypes

buffer_size = 1024
buffer = (ctypes.c_char * buffer_size)()
ctypes.memset(buffer, ord('A'), buffer_size)