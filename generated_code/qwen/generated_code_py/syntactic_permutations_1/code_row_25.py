import ctypes

def memcpy(dest, src, num_bytes):
    ctypes.memmove(dest, src, num_bytes)

# Example usage:
if __name__ == "__main__":
    # Create some example byte arrays
    source_array = (ctypes.c_char * 10).from_buffer_copy(b"abcdefghij")
    dest_array = (ctypes.c_char * 10)()

    # Copy 5 bytes from source to destination
    memcpy(dest_array, source_array, 5)

    # Print the result
    print(bytes(dest_array))  # Output: b'abcde\x00\x00\x00\x00'