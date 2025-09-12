import ctypes

size = 1024
source = (ctypes.c_char * size)()
destination = (ctypes.c_char * size)()

ctypes.memmove(destination, source, size)

print(destination.raw)

ctypes.POINTER(ctypes.c_char)().contents.value = destination
destination = None

print(destination)

ctypes.POINTER(ctypes.c_char)().contents.value = source
source = None