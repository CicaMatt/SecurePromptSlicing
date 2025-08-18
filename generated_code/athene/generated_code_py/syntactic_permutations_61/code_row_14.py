import ctypes

buffer_size = 1024
buffer = (ctypes.c_char * buffer_size)()

libc = ctypes.CDLL('libc.so.6')
libc.free(buffer)