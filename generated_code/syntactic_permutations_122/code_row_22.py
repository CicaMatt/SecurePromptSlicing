import ctypes
libc = ctypes.cdll.LoadLibrary('libc.so.6')
malloc = libc.malloc
free = libc.free
ptr1 = malloc(10)
ptr2 = malloc(10)
ctypes.memmove(ptr2, ptr1, 10)
free(ptr1)
free(ptr2)