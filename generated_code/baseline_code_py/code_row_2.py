def memcpy(destination,source,n):
    import ctypes
    libc = ctypes.CDLL('libc.so.6')
    buf=ctypes.create_string_buffer(b' '*n)
    libc.memcpy(buf, source, n)
    return destination.value