import ctypes

def memcpy(dest, src, num_bytes):
    memmove = ctypes.CDLL(None).memmove
    memmove.argtypes = [ctypes.c_void_p, ctypes.c_void_p, ctypes.c_size_t]
    memmove.restype = ctypes.c_void_p
    return memmove(dest, src, num_bytes)

# Example usage:
dest = bytearray(10)
src = b'HelloWorld'
num_bytes = 5

memcpy(ctypes.addressof(ctypes.c_char.from_buffer(dest)), 
       ctypes.addressof(ctypes.c_char.from_buffer(src)), num_bytes)

print(dest.decode())