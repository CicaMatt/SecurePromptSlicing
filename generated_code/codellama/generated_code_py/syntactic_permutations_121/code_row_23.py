import ctypes
libc = ctypes.CDLL("msvcrt")

a = ctypes.create_string_buffer(b"abcdefghijklmnopqrstuvwxyz\x00")
b = ctypes.create_string_buffer(26)
ctypes.memmove(b, a, 26)
print (b.raw)
libc.free(a)
print (b.raw)
libc.free(b)
