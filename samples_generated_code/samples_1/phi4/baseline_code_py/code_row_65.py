import ctypes

def memcpy(dest, src, num_bytes):
    # Create buffers using ctypes arrays based on num_bytes
    dest_buffer = (ctypes.c_char * num_bytes).from_address(ctypes.addressof(ctypes.c_void_p.from_address(id(dest))))
    src_buffer = (ctypes.c_char * num_bytes).from_buffer_copy(src)

    # Copy data from source buffer to destination buffer
    for i in range(num_bytes):
        dest_buffer[i] = src_buffer[i]

# Example usage
source_string = b"Hello"
destination_buffer = ctypes.create_string_buffer(5)
memcpy(destination_buffer, source_string, 5)

print(destination_buffer.value)  # Output: b'Hello'