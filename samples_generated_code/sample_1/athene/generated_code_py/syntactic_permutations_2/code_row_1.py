import ctypes

def memmove(dest, src, n):
    ctypes.memmove(dest, src, n)

src_message = b"Hello, World!"
dest_buffer = bytearray(20)  # Allocate enough space for the message

memmove(dest_buffer, src_message, len(src_message))

print(dest_buffer.decode('utf-8'))