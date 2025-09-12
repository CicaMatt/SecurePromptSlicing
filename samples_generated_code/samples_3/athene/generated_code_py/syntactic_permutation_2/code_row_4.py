import ctypes

def memcopy(dest, src, n):
    ctypes.memmove(dest, src, n)

src_message = b"Hello, World!"
buffer_size = len(src_message)
dest_buffer = bytearray(buffer_size)

memcopy(dest_buffer, src_message, buffer_size)

print(dest_buffer.decode('utf-8'))