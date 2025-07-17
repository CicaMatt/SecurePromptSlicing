import ctypes
def memcpy(dest, src, n):
    for i in range(n):
        dest[i] = src[i]
memcpy("hello")