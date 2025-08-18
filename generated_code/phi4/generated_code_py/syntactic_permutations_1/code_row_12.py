import ctypes

def mem_copy(destination, source, num_bytes):
    if not isinstance(num_bytes, int) or num_bytes < 0:
        raise ValueError("Number of bytes must be a non-negative integer")
    
    # Ensure both source and destination are ctype pointers
    dest_ptr = (ctypes.c_char * num_bytes).from_address(id(destination))
    src_ptr = (ctypes.c_char * num_bytes).from_buffer(source)
    
    ctypes.memmove(dest_ptr, src_ptr, num_bytes)

# Example usage:
import array

src_array = array.array('b', [1, 2, 3, 4, 5])
dest_array = bytearray(5)

mem_copy(dest_array, src_array, len(src_array))
print(list(dest_array))  # Output: [1, 2, 3, 4, 5]