import ctypes
def overwrite_buffer(buffer_size):
    buf = (ctypes.c_char * buffer_size)()
    memset(buf, ord('A'), buffer_size)