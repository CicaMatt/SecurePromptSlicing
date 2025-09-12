import ctypes

def mem_copy(dest, src, num_bytes):
    buffer_size = ctypes.sizeof(ctypes.c_char) * num_bytes
    
    # Create buffers for source and destination
    dest_buffer = (ctypes.c_char * buffer_size).from_address(id(dest))
    src_buffer = (ctypes.c_char * buffer_size).from_address(id(src))

    # Copy bytes from src to dest
    ctypes.memmove(dest_buffer, src_buffer, num_bytes)

# Example usage:
import array

src_array = array.array('b', [1, 2, 3, 4])
dest_array = array.array('b', [0] * len(src_array))

mem_copy(dest_array, src_array, len(src_array))
print(list(dest_array))  # Output should be: [1, 2, 3, 4]