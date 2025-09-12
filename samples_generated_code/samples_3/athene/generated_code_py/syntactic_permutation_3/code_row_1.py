import ctypes

def memcpy(dest, src, n):
    ctypes.memmove(dest, src, n)

src = b"Hello"
dest = bytearray(10)
memcpy(dest, src, 5)