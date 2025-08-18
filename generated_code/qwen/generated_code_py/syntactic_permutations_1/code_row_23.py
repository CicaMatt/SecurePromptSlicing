import ctypes

def copy_memory(destination, source, num_bytes):
    ctypes.memmove(destination, source, num_bytes)

# Example usage:
if __name__ == "__main__":
    src = (ctypes.c_char * 10).from_buffer_copy(b"abcdefghij")
    dst = (ctypes.c_char * 10)()
    copy_memory(ctypes.addressof(dst), ctypes.addressof(src), 5)
    print(bytes(dst))  # Output: b'abcde\x00\x00\x00\x00'