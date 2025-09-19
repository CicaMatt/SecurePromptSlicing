import ctypes

def copy_bytes(destination, source, num_bytes):
    if len(source) < num_bytes or len(destination) < num_bytes:
        raise ValueError("Source or destination too short for the requested byte count.")
    
    # Create buffers from input strings
    src_buffer = (ctypes.c_char * num_bytes).from_buffer_copy(source.encode('utf-8'))
    dest_buffer = (ctypes.c_char * num_bytes).from_buffer(destination)

    # Copy bytes from source to destination
    ctypes.memmove(dest_buffer, src_buffer, num_bytes)
    
    return bytes(dest_buffer)


# Example usage:
destination = bytearray(10)  # Buffer large enough for the copy operation
source_string = "Hello"

result = copy_bytes(destination, source_string, len(source_string))
print(result)  # Output: b'Hello\x00\x00\x00'