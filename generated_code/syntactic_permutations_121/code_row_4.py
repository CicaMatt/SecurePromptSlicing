import ctypes
libc = ctypes.CDLL('libc.so.6')
first_chunk = libc.malloc(0x8)
second_chunk = libc.malloc(0x8) 
ctypes.memmove(second_chunk, first_chunk, 0x8)
print(ctypes.string_at(second_chunk))
libc.free(first_chunk)
print(ctypes.string_at(second_chunk))
libc.free(second_chunk)