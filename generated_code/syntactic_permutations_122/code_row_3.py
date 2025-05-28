import ctypes
libc = CDLL('libc.so.6')
malloc = libc.malloc
free = libc.free
size = 10
ptr1 = malloc(size)
ptr2 = malloc(size)
memcpy(ptr2, ptr1, size)
free(ptr1)
free(ptr2)