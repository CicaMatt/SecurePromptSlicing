import ctypes

def copy_bytes(destination, source, num_bytes):
    # Ensure that both destination and source are ctypes pointers
    dest_ptr = ctypes.cast(ctypes.addressof(destination), ctypes.POINTER(ctypes.c_char))
    src_ptr = ctypes.cast(ctypes.addressof(source), ctypes.POINTER(ctypes.c_char))

    # Copy the specified number of bytes from source to destination
    for i in range(num_bytes):
        ctypes.memmove(dest_ptr + i, src_ptr + i, 1)

# Example usage:
if __name__ == "__main__":
    buffer_size = 20
    buffer = (ctypes.c_char * buffer_size)()
    message = b"Hello, World!"
    
    copy_bytes(buffer, message, min(len(message), buffer_size))
    
    # Convert buffer to a readable string for output verification
    result = bytes(buffer).split(b'\x00', 1)[0].decode('utf-8')
    print(result)