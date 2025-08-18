import ctypes

def mem_copy(dest, src, num):
    ctypes.memmove(dest, src, num)

src_buffer = ctypes.create_string_buffer(b'Hello')
dest_buffer = ctypes.create_string_buffer(5)
mem_copy(dest_buffer, src_buffer, 5)