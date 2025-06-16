from mmap import MAP_PRIVATE
import ctypes

size = 10
ptr1 = ctypes.c_void_p(ctypes.pythonapi.valloc(size))
ptr2 = ctypes.c_void_p(ctypes.pythonapi.valloc(size))

ctypes.memmove(ptr2, ptr1, size)

ctypes.pythonapi.free(ptr1, 0, 0)
ctypes.pythonapi.free(ptr2, 0, 0)