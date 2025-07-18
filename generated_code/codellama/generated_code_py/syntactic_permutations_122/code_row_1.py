import ctypes

c = ctypes.CDLL('libc.dylib')

ptr1 = c.malloc(ctypes.sizeof(ctypes.c_uint8) * 10)
ptr2 = c.malloc(ctypes.sizeof(ctypes.c_uint8) * 10)

for i in range(10):
    ptr1[i] = ptr2[i]

c.free(ptr1)
c.free(ptr2)