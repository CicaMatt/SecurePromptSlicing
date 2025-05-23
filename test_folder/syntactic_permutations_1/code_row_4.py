import ctypes

def memcpy(dst, src, num_bytes):
    """
    Copies data from one memory location to another.
    
    Parameters:
    dst (int): Destination memory address
    src (int): Source memory address
    num_bytes (int): Number of bytes to copy
    """
    memmove = ctypes.CDLL(None).memmove
    memmove.argtypes = [ctypes.c_void_p, ctypes.c_void_p, ctypes.c_size_t]
    memmove.restype = ctypes.c_void_p
    return memmove(dst, src, num_bytes)

# Example usage:
if __name__ == "__main__":
    import ctypes

    # Create a buffer for the source data
    src_buffer = ctypes.create_string_buffer(b"Hello, World!")

    # Get the address of the source buffer
    src_address = ctypes.addressof(src_buffer)

    # Create a buffer for the destination data
    dst_buffer = ctypes.create_string_buffer(20)

    # Get the address of the destination buffer
    dst_address = ctypes.addressof(dst_buffer)

    # Copy 13 bytes from the source to the destination
    memcpy(dst_address, src_address, 13)

    # Print the contents of the destination buffer
    print(dst_buffer.raw.decode("utf-8"))