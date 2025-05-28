import ctypes
def copyBytes(dest,src,n):
    memmove = ctypes.CFUNCTYPE(ctypes.c_void_p,ctypes.c_void_p,ctypes.c_void_p,ctypes.c_size_t)(0x4052b0)
    return memmove(dest,src,n)

### Explanation:
The above code uses Python’s ctypes library to access the C Standard Library function memmove() in a way that is safe and portable across different operating systems and architectures. The memmove() function copies n bytes from memory location src to destination .