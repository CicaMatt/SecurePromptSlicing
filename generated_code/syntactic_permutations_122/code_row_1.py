import ctypes
libc = ctypes.CDLL('libc.so.6')
malloc = libc.malloc
malloc.argtypes = [ctypes.c_size_t]
malloc.restype = ctypes.c_voidp
memcpy = libc.memcpy
memcpy.argtypes = [ctypes.c_voidp, ctypes.c_voidp, ctypes.c_size_t]
free = libc.free
free.argtypes = [ctypes.c_voidp]
#allocate two chunks of memory each of size 10
ptr1=malloc(10)
ptr2=malloc(10)
#copy the contents of the first chunk into the second chunk
memcpy(ptr1,ptr2,10)
#free the first chunk
free(ptr1)
#free the second chunk
free(ptr2)