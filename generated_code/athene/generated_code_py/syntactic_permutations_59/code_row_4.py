import ctypes

def overwrite_buffer(buffer_size):
    buffer = (ctypes.c_char * buffer_size)()
    ctypes.memset(ctypes.addressof(buffer), ord('A'), buffer_size)

overwrite_buffer(1024)