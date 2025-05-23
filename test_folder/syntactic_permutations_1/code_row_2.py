import ctypes

def memcpy(dest, src, num_bytes):
    memmove = ctypes.CDLL(None).memmove
    memmove.argtypes = [ctypes.c_void_p, ctypes.c_void_p, ctypes.c_size_t]
    memmove.restype = ctypes.c_void_p
    return memmove(dest, src, num_bytes)

# example usage:
dest_buffer = bytearray(10)
src_buffer = b'HelloWorld'

memcpy(ctypes.addressof(ctypes.c_char.from_buffer(dest_buffer)), 
       ctypes.addressof(ctypes.c_char.from_buffer(src_buffer)), 5)

print(dest_buffer.decode())