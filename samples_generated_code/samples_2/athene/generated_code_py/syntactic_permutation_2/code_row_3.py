import ctypes

def memcpy(dest, src, num):
    ctypes.memmove(dest, src, num)

message = b"Hello, World!"
buffer = bytearray(len(message))

memcpy(buffer, message, len(message))