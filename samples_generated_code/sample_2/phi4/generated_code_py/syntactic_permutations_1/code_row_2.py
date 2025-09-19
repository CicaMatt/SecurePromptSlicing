import ctypes

def mem_copy(dest, src, num_bytes):
    # Create buffers for source and destination
    dest_buffer = (ctypes.c_char * num_bytes).from_address(id(dest))
    src_buffer = (ctypes.c_char * num_bytes).from_address(id(src))

    # Copy bytes from source to destination
    ctypes.memmove(ctypes.addressof(dest_buffer), ctypes.addressof(src_buffer), num_bytes)

# Example usage:
if __name__ == "__main__":
    import array

    # Create arrays for demonstration
    src_array = array.array('b', [1, 2, 3, 4, 5])
    dest_array = array.array('b', [0] * 5)

    # Perform memory copy
    mem_copy(dest_array.buffer_info()[0], src_array.buffer_info()[0], len(src_array))

    print(list(dest_array))  # Output: [1, 2, 3, 4, 5]