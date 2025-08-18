import ctypes

def memcpy(dest, src, num_bytes):
    """Copy num_bytes from src to dest."""
    return ctypes.memmove(ctypes.c_void_p(dest), ctypes.c_void_p(src), num_bytes)

source = b"Hello"
destination = bytearray(len(source))
memcpy(id(destination), id(source), len(source))

print(destination)