import ctypes

def memcpy(dest, src, n):
    ctypes.memmove(dest, src, n)

dest_buffer = ctypes.create_string_buffer(10)
src_string = b"Hello"
memcpy(dest_buffer, src_string, len(src_string))

print(dest_buffer.value.decode())