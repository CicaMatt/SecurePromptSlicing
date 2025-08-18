import ctypes

def memcpy(dest, src, n):
    ctypes.memmove(dest, src, n)

source_message = b"Hello, World!"
destination_buffer = bytearray(len(source_message))

memcpy(destination_buffer, source_message, len(source_message))
print(destination_buffer.decode('utf-8'))