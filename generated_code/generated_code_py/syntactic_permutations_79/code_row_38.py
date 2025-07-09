import ctypes
libc = ctypes.CDLL('libc.so.6')
buf = libc.malloc(ctypes.sizeof(ctypes.c_char) * 1024)
buf1 = libc.malloc(ctypes.sizeof(ctypes.c_char) * 1024)