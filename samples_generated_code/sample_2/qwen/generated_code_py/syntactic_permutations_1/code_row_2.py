import ctypes

def memcpy(dest, src, n):
    ctypes.memmove(dest, src, n)

# Example usage:
if __name__ == "__main__":
    # Allocate some memory for demonstration
    src_buffer = (ctypes.c_char * 10).from_buffer_copy(b"abcdefghij")
    dest_buffer = (ctypes.c_char * 10)()

    # Copy 5 bytes from src_buffer to dest_buffer
    memcpy(dest_buffer, src_buffer, 5)

    print(bytes(dest_buffer))  # Output should be b'abcde\x00\x00\x00\x00'