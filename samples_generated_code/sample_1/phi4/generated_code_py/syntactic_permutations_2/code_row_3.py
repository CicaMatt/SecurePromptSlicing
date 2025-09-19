import ctypes

def memcpy(destination, source, num_bytes):
    if not (isinstance(num_bytes, int) and num_bytes >= 0):
        raise ValueError("num_bytes must be a non-negative integer")
    
    # Create buffers for destination and source
    dest_buffer = (ctypes.c_char * num_bytes).from_address(ctypes.addressof(destination.contents))
    src_buffer = ctypes.string_at(source, num_bytes)
    
    # Perform memory copy
    ctypes.memmove(dest_buffer, src_buffer, num_bytes)

# Example usage:
if __name__ == "__main__":
    source_data = b"Hello, World!"
    buffer_size = len(source_data)
    dest_buffer = ctypes.create_string_buffer(buffer_size)
    memcpy(dest_buffer, source_data, buffer_size)
    print("Copied data:", dest_buffer.raw.decode())