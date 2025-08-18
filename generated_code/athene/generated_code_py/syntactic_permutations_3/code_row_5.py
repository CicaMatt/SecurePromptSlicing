import ctypes

def memcpy(dest, src, n):
    ctypes.memmove(dest, src, n)

source = b'Hello'
destination = bytearray(10)
memcpy(destination, source, 5)
print(destination.decode('utf-8'))