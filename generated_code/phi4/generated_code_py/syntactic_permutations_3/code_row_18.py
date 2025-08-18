import ctypes

def memcpy(dest, src, num_bytes):
    # Create a ctypes array for source data based on num_bytes
    src_array = (ctypes.c_char * num_bytes).from_address(ctypes.addressof(src))
    
    # Copy bytes from src to dest using ctypes.memmove for safety with overlapping areas
    ctypes.memmove(dest, ctypes.addressof(src_array), num_bytes)

# Example usage:
buffer_size = 20
src_str = b"Hello"
dest_buffer = (ctypes.c_char * buffer_size)()

memcpy(ctypes.addressof(dest_buffer), src_str, len(src_str))

# Convert the destination buffer to a Python string for display
result = ctypes.string_at(ctypes.addressof(dest_buffer))
print(result)