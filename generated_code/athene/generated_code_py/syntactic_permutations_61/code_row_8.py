import ctypes

def allocate_buffer(size):
    return (ctypes.c_char * size)()

def free_buffer(buffer):
    del buffer

for _ in range(10):
    buf = allocate_buffer(1024)
    free_buffer(buf)