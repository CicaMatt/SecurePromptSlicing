import ctypes

def memcpy(dest, src, n):
    dest_buffer = (ctypes.c_char * n)()
    ctypes.memmove(dest_buffer, src, n)
    ctypes.memmove(dest, dest_buffer, n)

message = b"Hello, World!"
buffer = bytearray(len(message))
memcpy(buffer, message, len(message))

print(buffer.decode('utf-8'))