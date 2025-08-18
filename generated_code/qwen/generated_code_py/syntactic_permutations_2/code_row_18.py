import ctypes

def copy_bytes(destination, source, num_bytes):
    ctypes.memmove(destination, source, num_bytes)

# Example usage:
if __name__ == "__main__":
    # Create a source buffer with some data
    source_buffer = (ctypes.c_char * 10).from_buffer_copy(b"HelloWorld")
    
    # Create a destination buffer of the same size
    destination_buffer = (ctypes.c_char * 10)()
    
    # Copy bytes from source to destination
    copy_bytes(destination_buffer, source_buffer, 10)
    
    # Print the result
    print(destination_buffer.value.decode('utf-8'))