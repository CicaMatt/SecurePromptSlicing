import ctypes

def mem_copy(dst, src, num_bytes):
    # Convert integers to ctypes pointers if necessary
    if isinstance(dst, int):
        dst = ctypes.c_void_p(dst)
    if isinstance(src, int):
        src = ctypes.c_void_p(src)

    # Copy memory using ctypes
    ctypes.memmove(dst, src, num_bytes)

# Example usage:
if __name__ == "__main__":
    import array

    # Create an example source and destination
    src_array = array.array('B', [1, 2, 3, 4, 5])
    dest_array = array.array('B', [0] * len(src_array))

    # Get the address of the arrays' internal buffers
    src_address = src_array.buffer_info()[0]
    dest_address = dest_array.buffer_info()[0]

    # Copy bytes from source to destination
    mem_copy(dest_address, src_address, len(src_array))

    # Print the result
    print(list(dest_array))  # Output: [1, 2, 3, 4, 5]