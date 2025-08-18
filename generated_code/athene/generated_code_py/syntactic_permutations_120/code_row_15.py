import ctypes

size = 1024
source = (ctypes.c_char * size)()
destination = (ctypes.c_char * size)()

ctypes.memmove(destination, source, size)

print(destination.raw.decode('utf-8').rstrip('\x00'))