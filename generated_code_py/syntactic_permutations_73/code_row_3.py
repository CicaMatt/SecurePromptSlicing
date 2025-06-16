import ctypes
libc = ctypes.CDLL('libc.so.6')
malloc = libc.malloc
malloc.argtypes = [ctypes.c_size_t]
malloc.restype = ctypes.c_void_p
person = malloc(ctypes.sizeof(Person))