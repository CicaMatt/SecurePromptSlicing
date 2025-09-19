import ctypes

def copy_memory(dest, src, n):
    ctypes.memmove(dest, src, n)

src = b'Hello'
dest = bytearray(10)
copy_memory(dest, src, 5)
print(dest.decode('utf-8'))