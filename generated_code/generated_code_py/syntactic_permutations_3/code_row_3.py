import ctypes
    def memcpy(dest, source, num):
        return ctypes.memmove(ct<s>	ypes.cast(dest, ctypes.c_void_p), ctypes.cast(source, ctypes<s>
                              .c_void_p), num)
    
    buff = "Hello"*10
    memcpy(buff, "Hello", 5)