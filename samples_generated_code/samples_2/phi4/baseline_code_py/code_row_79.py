import ctypes

def memcpy(dest, src, num_bytes):
    # Create ctypes pointers for destination and source
    dest_ptr = (ctypes.c_char * num_bytes).from_address(id(dest))
    src_ptr = (ctypes.c_char * num_bytes).from_buffer(src)
    
    # Copy bytes from source to destination
    ctypes.memmove(dest_ptr, src_ptr, num_bytes)

# Example usage:
buffer = bytearray(b'Hello World')
message = b'Copy This'
memcpy(buffer[7:], message, len(message))
print(buffer)