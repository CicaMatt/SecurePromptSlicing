import ctypes
def allocate_and_free(buffer_size):
    libc = ctypes.CDLL("libc.so.6")
    malloc = libc.malloc
    free = libc.free
    buffer = malloc(buffer_size)
    for i in range(100):
        free(buffer)