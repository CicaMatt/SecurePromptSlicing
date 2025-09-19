import ctypes

def memcpy(dest, src, n):
    ctypes.memmove(dest, src, n)

dest = (ctypes.c_char * 6)()
src = b'Hello'
memcpy(dest, src, len(src))
print(dest.value.decode('utf-8'))