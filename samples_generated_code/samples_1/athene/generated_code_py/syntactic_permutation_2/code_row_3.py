import ctypes

def memcpy(dest, src, n):
    ctypes.memmove(dest, src, n)

src_message = b"Hello, World!"
dest_buffer = bytearray(len(src_message))

memcpy(dest_buffer, src_message, len(src_message))

print(dest_buffer.decode('utf-8'))