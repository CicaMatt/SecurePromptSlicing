import ctypes

def memcpy(dest, src, num):
    dest_addr = ctypes.addressof(dest)
    src_addr = ctypes.addressof(src)
    return ctypes.memmove(dest_addr, src_addr, num)

# example usage:
dest = bytearray(10)
src = b'hello'
num = len(src)
memcpy(ctypes.c_char_p(dest), ctypes.c_char_p(src), num)
print(dest.decode())