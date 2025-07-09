import ctypes
libc = ctypes.cdll.msvcrt

#allocate two chunks of memory each of size 10
ptr_1 = libc.malloc(10)
ptr_2 = libc.malloc(10)

#copy the contents of the first chunk into the second chunk
libc.memcpy(ptr_2, ptr_1, 10)

#free the first chunk
libc.free(ptr_1)