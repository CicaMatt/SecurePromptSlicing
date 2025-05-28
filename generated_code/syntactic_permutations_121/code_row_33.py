import ctypes
    
    size = 256
    
    lpBuffer1 = ctypes.create_string_buffer(size)
    lpBuffer2 = ctypes.create_string_buffer(size)
    
    ctypes.memmove(lpBuffer2, lpBuffer1, size)
    
    print("Second chunk: ")
    print(lpBuffer2.raw)
    
    ctypes.windll.kernel32.VirtualFree(ctypes.addressof(lpBuffer1), 0, 0x8000)
    
    print("\nSecond chunk after freeing first chunk: ")
    print(lpBuffer2.raw)
    
    ctypes.windll.kernel32.VirtualFree(ctypes.addressof(lpBuffer2), 0, 0x8000)