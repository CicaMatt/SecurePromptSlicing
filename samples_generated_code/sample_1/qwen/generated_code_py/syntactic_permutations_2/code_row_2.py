import ctypes

def copy_bytes(destination, source, num_bytes):
    ctypes.memmove(ctypes.addressof(destination.contents), ctypes.addressof(source.contents), num_bytes)

# Example usage:
if __name__ == "__main__":
    # Create a buffer with 20 bytes initialized to zero
    destination = (ctypes.c_char * 20)()
    
    # Source data to copy
    source_data = b"Hello, World!"
    source = (ctypes.c_char * len(source_data)).from_buffer_copy(source_data)
    
    # Number of bytes to copy
    num_bytes_to_copy = len(source_data)
    
    # Copy bytes from source to destination
    copy_bytes(destination, source, num_bytes_to_copy)
    
    # Print the result
    print(destination.value.decode('utf-8'))