import ctypes
libc = ctypes.cdll.LoadLibrary('libc.so.6')
malloc = libc.malloc
free = libc.free
chunk1 = malloc(10)
chunk2 = malloc(10)
ctypes.memmove(chunk2, chunk1, 10)
free(chunk1)
free(chunk2)