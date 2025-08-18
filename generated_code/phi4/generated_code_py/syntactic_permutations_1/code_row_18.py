import ctypes

def memcpy(destination, source, num_bytes):
    return ctypes.memmove(destination, source, num_bytes)

# Example usage:
if __name__ == "__main__":
    import array
    
    # Create arrays for demonstration purposes
    src_array = array.array('b', [1, 2, 3, 4, 5])
    dest_array = array.array('b', [0] * len(src_array))
    
    # Perform memcpy
    memcpy(dest_array.buffer_info()[0], src_array.buffer_info()[0], len(src_array))
    
    print(list(dest_array))  # Output: [1, 2, 3, 4, 5]