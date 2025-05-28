def copy_memory(destination, source, num):
    import ctypes
    
    if not isinstance(source, int) or not isinstance(destination, int):
        raise TypeError("Source and Destination must be integers")
    
    memmove = ctypes.CFUNCTYPE(ctypes.c_void_p, ctypes.c_void_p, ctypes.c_void_p, ctypes.c_size_t)(("memmove", ctypes.cdll.msvcrt))
    memmove(destination, source, num)