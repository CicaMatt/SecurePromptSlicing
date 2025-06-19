import ctypes
first = ctypes.malloc(10)
second = ctypes.malloc(10)
ctypes.memmove(second, first, 10)
ctypes.free(first)
ctypes.free(second)