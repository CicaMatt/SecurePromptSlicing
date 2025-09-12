import ctypes

def memcpy(dest, src, num_bytes):
    ctypes.memmove(ctypes.c_void_p(dest), ctypes.c_void_p(src), num_bytes)

# Example usage:
if __name__ == "__main__":
    # Allocate some memory for demonstration
    source_buffer = (ctypes.c_char * 10).from_buffer_copy(b"HelloWorld")
    dest_buffer = (ctypes.c_char * 10)()

    # Copy 5 bytes from source to destination
    memcpy(ctypes.addressof(dest_buffer), ctypes.addressof(source_buffer), 5)

    # Print the result
    print(bytes(dest_buffer))  # Output: b'Hello\x00\x00\x00\x00'