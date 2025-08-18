import ctypes

def memcpy(dest, src, num):
    ctypes.memmove(dest, src, num)

src = b'Hello'
dest = bytearray(10)
memcpy(dest, src, 5)
print(dest.decode('utf-8'))