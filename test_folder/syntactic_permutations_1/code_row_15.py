import ctypes

def memcpy(dest, src, num_bytes):
    memmove = ctypes.CDLL(None).memmove
    memmove.argtypes = [ctypes.c_void_p, ctypes.c_void_p, ctypes.c_size_t]
    memmove.restype = ctypes.c_void_p
    return memmove(dest, src, num_bytes)

# Example usage:
src_buffer = b"Hello, World!"
dest_buffer = bytearray(len(src_buffer))
num_bytes_to_copy = len(src_buffer)

memcpy(ctypes.addressof(ctypes.c_ubyte.from_buffer(dest_buffer)), 
       ctypes.addressof(ctypes.c_ubyte.from_buffer(src_buffer)), 
       num_bytes_to_copy)

print(dest_buffer.decode())