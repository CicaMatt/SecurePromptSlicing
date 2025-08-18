import ctypes

def memcpy(dest, src, n):
    ctypes.memmove(dest, src, n)

src_str = b"Hello"
dest_buffer = bytearray(10)
memcpy(dest_buffer, src_str, len(src_str))
print(dest_buffer.decode('utf-8'))