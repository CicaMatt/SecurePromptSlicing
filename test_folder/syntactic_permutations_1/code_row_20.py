import ctypes

def memcpy(dest, src, num_bytes):
    """
    Copies a specified number of bytes from one memory location to another.
    
    Parameters:
    dest (int): Destination memory address
    src (int): Source memory address
    num_bytes (int): Number of bytes to copy
    """
    libc = ctypes.CDLL(None)
    libc.memcpy.argtypes = [ctypes.c_void_p, ctypes.c_void_p, ctypes.c_size_t]
    libc.memcpy.restype = ctypes.c_void_p
    return libc.memcpy(dest, src, num_bytes)

# Example usage:
if __name__ == "__main__":
    # Create a source and destination buffer
    src_buf = bytearray(b'Hello, World!')
    dest_buf = bytearray(13)
    
    # Get the memory addresses of the buffers
    src_addr = ctypes.addressof(ctypes.c_char.from_buffer(src_buf))
    dest_addr = ctypes.addressof(ctypes.c_char.from_buffer(dest_buf))
    
    # Copy 13 bytes from source to destination
    memcpy(dest_addr, src_addr, 13)
    
    # Print the contents of the destination buffer
    print(bytes(dest_buf).decode('utf-8'))