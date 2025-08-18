import ctypes

def memcpy(dest, src, num):
    ctypes.memmove(dest, src, num)

src_str = b"Hello"
dest_buffer = bytearray(10)
memcpy(dest_buffer, src_str, 5)
print(dest_buffer.decode('utf-8'))