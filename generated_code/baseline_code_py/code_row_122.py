import ctypes
libc = ctypes.CDLL('libc.so.6')
c_void_p = ctypes.c_void_p
malloc = libc.malloc
malloc.restype = c_void_p
malloc.argtypes = [ctypes.c_size_t]
free = libc.free
free.restype = None
free.argtypes = [c_void_p]

def main():
    chunk1 = malloc(10)
    chunk2 = malloc(10)
    memcpy(chunk2, chunk1, 10)
    free(chunk1)
    free(chunk2)