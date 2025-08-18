import ctypes

def memcpy(dest, src, num_bytes):
    ctypes.memmove(ctypes.c_void_p(dest), ctypes.c_void_p(src), num_bytes)

# Example usage:
if __name__ == "__main__":
    # Allocate some memory for demonstration
    source = (ctypes.c_char * 10).from_buffer_copy(b"abcdefghij")
    destination = (ctypes.c_char * 10)()

    # Copy 5 bytes from source to destination
    memcpy(ctypes.addressof(destination), ctypes.addressof(source), 5)

    print(bytes(destination))  # Output should be b'abcde\x00\x00\x00\x00'