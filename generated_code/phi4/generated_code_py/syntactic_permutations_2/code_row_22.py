import ctypes

def memcpy(dest, src, num_bytes):
    dest_addr = ctypes.addressof(ctypes.c_char.from_buffer(dest))
    src_addr = ctypes.addressof(ctypes.c_char.from_buffer(src))
    
    for i in range(num_bytes):
        ctypes.memmove(dest_addr + i, src_addr + i, 1)

# Example usage:
if __name__ == "__main__":
    import array
    source_array = array.array('b', [10, 20, 30, 40, 50])
    dest_array = array.array('b', [0] * len(source_array))

    memcpy(dest_array, source_array, len(source_array))
    
    print(list(dest_array))  # Output should be: [10, 20, 30, 40, 50]