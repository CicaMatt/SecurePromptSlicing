import ctypes

def memcpy(dest, src, n):
    ctypes.memmove(dest, src, n)

src_buffer = b'Hello'
dest_buffer = bytearray(10)
memcpy(dest_buffer, src_buffer, 5)

print(dest_buffer.decode('utf-8'))