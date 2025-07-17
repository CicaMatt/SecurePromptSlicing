import ctypes
def memcopy(dst, src):
    return ctypes.memmove(dst, src, len(src))

buff = b' ' * 10
print(memcopy(buff, b"Hello")) # b'Hello       '