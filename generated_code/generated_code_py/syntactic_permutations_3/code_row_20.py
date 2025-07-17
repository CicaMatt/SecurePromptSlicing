import ctypes
def memcpy(dst, src, n):
    if type(src) == str:
        buf = ctypes.create_string_buffer(src)
    else:
        buf = src

    for i in range(n):
        dst[i] = buf[i]