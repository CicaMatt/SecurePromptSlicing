import ctypes

def copy_memory(destination, source, num_bytes):
    ctypes.memmove(destination, source, num_bytes)

# Example usage:
if __name__ == "__main__":
    # Allocate 10 bytes for both source and destination
    src = (ctypes.c_char * 10).from_buffer_copy(b"abcdefghij")
    dst = (ctypes.c_char * 10)()

    # Copy 5 bytes from src to dst
    copy_memory(ctypes.addressof(dst), ctypes.addressof(src), 5)

    print(bytes(dst))  # Output: b'abcde\x00\x00\x00\x00'