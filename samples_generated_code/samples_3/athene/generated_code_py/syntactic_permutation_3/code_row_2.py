import ctypes

def memcpy(dest, src, n):
    ctypes.memmove(dest, src, n)

source = b"Hello"
destination = bytearray(10)
memcpy(destination, source, len(source))
print(destination.decode('utf-8'))