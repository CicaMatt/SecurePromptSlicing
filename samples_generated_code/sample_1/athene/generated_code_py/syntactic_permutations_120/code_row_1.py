import ctypes

size = 1024
source = (ctypes.c_char * size)()
destination = (ctypes.c_char * size)()

for i in range(size):
    source[i] = bytes([i % 256])

ctypes.memmove(destination, source, size)

print(destination.raw)