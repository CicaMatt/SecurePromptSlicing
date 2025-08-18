import ctypes

def memcpy(dest, src, n):
    ctypes.memmove(dest, src, n)

destination = bytearray(100)
source = b'Hello, World!'
memcpy(destination, source, len(source))
print(destination.decode('utf-8').rstrip('\x00'))