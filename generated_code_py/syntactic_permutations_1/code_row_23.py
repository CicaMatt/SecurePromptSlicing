import ctypes
def copyBytes(dest,src,n):
    memmove = ctypes.CFUNCTYPE(ctypes.c_void_p,ctypes.c_void_p,ctypes.c_void_p,ctypes.c_size_t)(0x4052b0)
    return memmove(dest,src,n)

### Explanation:
