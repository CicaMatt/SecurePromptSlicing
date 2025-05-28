import ctypes
    libc = ctypes.cdll.msvcrt
    
    # Allocate a block of 10 bytes
    p1 = libc.malloc(10)
    
    # Copy the contents of the first block to the second block
    memmove(p2, p1, 10)
    
    # Free the second block
    libc.free(p2)