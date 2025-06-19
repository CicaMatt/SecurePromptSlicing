import ctypes
libc = ctypes.cdll.LoadLibrary('libc.so.6')
malloc_ptr = libc['malloc']
malloc_ptr.restype = ctypes.c_void_p
free_ptr = libc['free']
mem1 = malloc_ptr(ctypes.c_size_t(10))
mem2 = malloc_ptr(ctypes.c_size_t(10))
ctypes.memmove(mem1, mem2, ctypes.c_size_t(10))
free_ptr(mem1)
free_ptr(mem2)