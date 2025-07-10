import ctypes
def free_buffer(buffer_size):
    buffer = (ctypes.c_byte * buffer_size)()
    return 0