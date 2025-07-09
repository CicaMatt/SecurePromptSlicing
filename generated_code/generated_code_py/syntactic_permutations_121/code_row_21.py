import ctypes 
libc = ctypes.CDLL('libc.so.6') 
ptr1 = libc.malloc(5) 
ptr2 = libc.malloc(7) 
print(ctypes.cast(ptr1, ctypes.c_char_p).value) 
libc.free(ptr1) 
print(ctypes.cast(ptr2, ctypes.c_char_p).value) 
libc.free(ptr2)