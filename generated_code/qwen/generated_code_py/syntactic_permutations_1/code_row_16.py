import ctypes

def memcopy(dest, src, n):
    ctypes.memmove(ctypes.c_void_p(dest), ctypes.c_void_p(src), n)

# Example usage:
if __name__ == "__main__":
    # Allocate some memory for demonstration
    source_buffer = (ctypes.c_char * 10).from_buffer_copy(b"abcdefghij")
    dest_buffer = (ctypes.c_char * 10)()

    # Copy 5 bytes from source to destination
    memcopy(ctypes.addressof(dest_buffer), ctypes.addressof(source_buffer), 5)

    print(bytes(dest_buffer))  # Output: b'abcde\x00\x00\x00\x00'