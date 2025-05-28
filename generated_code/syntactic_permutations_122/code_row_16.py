import ctypes
libc = ctypes.cdll.msvcrt

ptr_one = libc.malloc(10)
ptr_two = libc.malloc(10)

libc.memcpy(ptr_two, ptr_one, 10)

libc.free(ptr_one)
libc.free(ptr_two)