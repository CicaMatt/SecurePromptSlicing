import ctypes
libc = CDLL('libc.so.6')
m1 = libc.malloc(ctypes.sizeof(ctypes.c_int * 4))
m2 = libc.malloc(ctypes.sizeof(ctypes.c_int * 5))
libc.memcpy(m1, m2, ctypes.sizeof(ctypes.c_int * 4))
print(m1)
libc.free(m1)
print(m2)
libc.free(m2)