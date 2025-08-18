import ctypes

def allocate_and_free_buffer(size, iterations):
    for _ in range(iterations):
        buffer = (ctypes.c_char * size)()
        ctypes.memset(buffer, 0, size)
        del buffer

allocate_and_free_buffer(1024, 1000)