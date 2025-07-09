import ctypes
libc = ctypes.CDLL('libc.so.6')
malloc = libc.malloc
free = libc.free
first_chunk = malloc(10)
second_chunk = malloc(10)
ctypes.memmove(ctypes.addressof(second_chunk.contents), ctypes.addressof(first_chunk.contents), 10)
free(first_chunk)
free(second_chunk)