import ctypes

def copy_bytes(dest, src, num_bytes):
    if not (0 <= num_bytes <= 256):
        raise ValueError("Number of bytes to copy must be between 0 and 256")
    
    # Ensure both dest and src are pointers to at least num_bytes
    if not isinstance(dest, ctypes.c_void_p) or not isinstance(src, ctypes.c_void_p):
        raise TypeError("Both dest and src must be c_void_p instances")
    
    ctypes.memmove(dest, src, num_bytes)

# Example usage:
if __name__ == "__main__":
    # Create two buffers of 256 bytes each
    buffer1 = (ctypes.c_char * 256)()
    buffer2 = (ctypes.c_char * 256)()

    # Fill buffer1 with some data
    for i in range(256):
        buffer1[i] = chr(i % 256).encode('latin-1')

    # Copy 100 bytes from buffer1 to buffer2
    copy_bytes(ctypes.byref(buffer2), ctypes.byref(buffer1), 100)

    # Print the first 100 bytes of buffer2 to verify the copy
    print([buffer2[i] for i in range(100)])