import ctypes

def mem_copy(dest, src, num_bytes):
    # Ensure both dest and src are instances of ctypes.c_char_p or similar types.
    if not isinstance(dest, (ctypes.Array, ctypes._CData)) or not isinstance(src, (ctypes.Array, ctypes._CData)):
        raise TypeError("dest and src must be ctypes memory objects.")
    
    # Calculate the number of elements that can actually be copied
    num_elements = min(len(dest), len(src), num_bytes)
    
    # Use ctypes.memmove for safe copying between overlapping regions
    ctypes.memmove(dest, src, num_elements)

# Example usage:
source_buffer = (ctypes.c_char * 20).from_string(b'Hello, this is a source buffer.')
destination_buffer = (ctypes.c_char * 20)()

mem_copy(destination_buffer, source_buffer, 18)

print(destination_buffer.raw)