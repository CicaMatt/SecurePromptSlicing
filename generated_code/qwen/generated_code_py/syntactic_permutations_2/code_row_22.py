import ctypes

def memcpy(dest, src, num_bytes):
    ctypes.memmove(dest, src, num_bytes)

# Example usage:
if __name__ == "__main__":
    # Allocate memory for demonstration
    source = (ctypes.c_char * 10).from_buffer_copy(b"abcdefghij")
    destination = (ctypes.c_char * 10)()

    # Copy 5 bytes from source to destination
    memcpy(destination, source, 5)

    print(bytes(destination))  # Output: b'abcde\x00\x00\x00\x00'