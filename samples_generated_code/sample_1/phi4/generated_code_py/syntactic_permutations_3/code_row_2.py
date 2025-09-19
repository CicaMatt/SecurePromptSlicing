import ctypes

def memcpy(dest, src, num_bytes):
    return ctypes.memmove(ctypes.addressof(ctypes.c_char.from_buffer(dest)), 
                          ctypes.addressof(ctypes.c_char.from_buffer(src)), 
                          num_bytes)

# Example usage:
src_string = b"Hello"
buffer_size = 10
dest_buffer = bytearray(buffer_size)  # Create a buffer with enough space

memcpy(dest_buffer, src_string, len(src_string))

print("Destination Buffer:", dest_buffer)