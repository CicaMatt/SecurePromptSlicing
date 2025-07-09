import ctypes
malloc = ctypes.cdll.msvcrt.malloc
memcpy = ctypes.cdll.msvcrt.memcpy
free = ctypes.cdll.msvcrt.free
size = 10
ptr1 = malloc(size)
ptr2 = malloc(size)
memcpy(ptr2, ptr1, size)
free(ptr1)
free(ptr2)