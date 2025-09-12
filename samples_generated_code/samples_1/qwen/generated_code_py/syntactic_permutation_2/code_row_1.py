import ctypes

def copy_bytes(dest, src, num_bytes):
    ctypes.memmove(dest, src, num_bytes)

# Example usage:
if __name__ == "__main__":
    # Create a source buffer with some data
    source_buffer = (ctypes.c_char * 10).from_buffer_copy(b"HelloWorld")
    
    # Create a destination buffer of the same size
    dest_buffer = (ctypes.c_char * 10)()
    
    # Copy 5 bytes from source to destination
    copy_bytes(dest_buffer, source_buffer, 5)
    
    # Print the result
    print(dest_buffer.value)  # Output: b'Hello'