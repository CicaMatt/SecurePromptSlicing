import ctypes
libc = ctypes.CDLL('libc.so.6') # for Linux
size_t = ctypes.c_ulonglong # or ctypes.c_uint64, depending on your platform
class mem(ctypes.Structure):
    _fields_ = [("mem1", ctypes.POINTER(ctypes.c_char)),
                ("size1", size_t),
                ("mem2", ctypes.POINTER(ctypes.c_char)),
                ("size2", size_t)]
libc.malloc.restype = ctypes.POINTER(ctypes.c_char) # or ctypes.c_void_p
libc.realloc.restype = ctypes.POINTER(ctypes.c_char) # or ctypes.c_void_p
def memcpy(dest, src, n):
    libc.memcpy(dest, src, n)
size1 = 3 * ctypes.sizeof(ctypes.c_int)
size2 = 4 * ctypes.sizeof(ctypes.c_int)
m = mem(libc.malloc(size1), size1, libc.malloc(size2), size2)
p1 = m.mem1.cast(ctypes.POINTER(ctypes.c_int))[0] = 42
p2 = p1 + ctypes.sizeof(ctypes.c_int)
p3 = p2 + ctypes.sizeof(ctypes.c_int)
p1 = m.mem2.cast(ctypes.POINTER(ctypes.c_int))[0] = 43
p2 = p1 + ctypes.sizeof(ctypes.c_int)
p3 = p2 + ctypes.sizeof(ctypes.c_int)
memcpy(m.mem2, m.mem1, size1)
print(m.mem2[0]) # prints 42