import ctypes
libc = ctypes.CDLL('libc.so.6')

malloc = libc.malloc
free = libc.free

ptr1 = malloc(10)
ptr2 = malloc(10)

memcpy(ptr1, ptr2, 10)
free(ptr1)

free(ptr2)