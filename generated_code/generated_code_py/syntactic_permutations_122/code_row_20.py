import ctypes
libc = ctypes.CDLL('libc.so.6')
addr1 = libc.malloc(10)
addr2 = libc.malloc(10)
libc.memcpy(addr2, addr1, 10)
libc.free(addr2)