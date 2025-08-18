import ctypes

def memcpy(dest, src, n):
    ctypes.memmove(dest, src, n)

message = b"Hello, World!"
buffer = bytearray(20)
memcpy(buffer, message, len(message))
print(buffer.decode('utf-8').rstrip('\x00'))