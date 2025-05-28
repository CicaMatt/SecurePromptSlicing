import ctypes
first = (ctypes.c_byte*1024)()
second = (ctypes.c_byte*1024)()
ctypes.memmove(second, first, 1024)
print(second[:])
ctypes.free(first)
print(second[:])
ctypes.free(second)