import ctypes
libc = ctypes.CDLL('libc.so.6')

first_chunk = libc.malloc(10)
second_chunk = libc.malloc(10)

ctypes.memmove(second_chunk, first_chunk, 10)

libc.free(first_chunk)
libc.free(second_chunk)