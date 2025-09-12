import ctypes

def copy_bytes(dest, src, num_bytes):
    ctypes.memmove(ctypes.addressof(dest), ctypes.addressof(src), num_bytes)

# Example usage:
if __name__ == "__main__":
    # Create a source buffer with some data
    source_buffer = (ctypes.c_char * 10).from_buffer_copy(b"HelloWorld")
    
    # Create a destination buffer of the same size
    dest_buffer = (ctypes.c_char * 10)()
    
    # Copy 5 bytes from source to destination
    copy_bytes(dest_buffer, source_buffer, 5)
    
    # Convert to string and print the result
    print(dest_buffer.value[:5].decode())  # Output: Hello