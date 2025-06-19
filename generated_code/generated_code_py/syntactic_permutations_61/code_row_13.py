import ctypes
def free_buffer(buffer):
    if buffer == 0:
        return
    libc = ctypes.CDLL('libc.so.6')
    libc.free(buffer)