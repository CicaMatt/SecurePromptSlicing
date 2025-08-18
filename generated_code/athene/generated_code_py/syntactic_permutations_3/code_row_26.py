import ctypes

def memcpy(dest, src, n):
    ctypes.memmove(dest, src, n)

src_str = b"Hello"
dest_buffer = (ctypes.c_char * len(src_str))()

memcpy(dest_buffer, src_str, len(src_str))

print(dest_buffer.value.decode())