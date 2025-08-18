import ctypes

def memmove(dest, src, count):
    ctypes.memmove(dest, src, count)

src_buffer = ctypes.create_string_buffer(b'Hello')
dest_buffer = ctypes.create_string_buffer(5)
memmove(dest_buffer, src_buffer, 5)