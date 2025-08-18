import ctypes

def memcpy(dest, src, n):
    ctypes.memmove(dest, src, n)

message = b"Hello, World!"
buffer = bytearray(len(message))

memcpy(buffer, message, len(message))
print(buffer)