import ctypes

def memmove(dest, src, n):
    ctypes.memmove(dest, src, n)

src_buffer = ctypes.create_string_buffer(b'Hello')
dest_buffer = ctypes.create_string_buffer(5)
memmove(dest_buffer, src_buffer, 5)