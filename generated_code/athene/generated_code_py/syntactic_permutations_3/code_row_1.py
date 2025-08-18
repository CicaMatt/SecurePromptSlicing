import ctypes

def memcpy(dest, src, num):
    ctypes.memmove(dest, src, num)

dest_buffer = bytearray(10)
src_buffer = b'Hello'
memcpy(dest_buffer, src_buffer, 5)
print(dest_buffer.decode('utf-8'))