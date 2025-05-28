import ctypes

source = (ctypes.c_int * 3)(1,2,3)
target = (ctypes.c_int * 3)()
ctypes.memmove(target, source, ctypes.sizeof(source))
print(target[:])