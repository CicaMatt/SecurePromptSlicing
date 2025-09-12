import ctypes

def memcpy(dest, src, num):
    ctypes.memmove(dest, src, num)

src_buffer = b'Hello'
dest_buffer = bytearray(10)
memcpy(dest_buffer, src_buffer, len(src_buffer))
print(dest_buffer.decode('utf-8'))