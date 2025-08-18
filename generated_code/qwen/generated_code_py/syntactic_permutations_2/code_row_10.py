import ctypes

def copy_bytes(dest, src, num_bytes):
    ctypes.memmove(ctypes.addressof(dest), ctypes.addressof(src), num_bytes)

# Example usage:
if __name__ == "__main__":
    source_buffer = (ctypes.c_char * 10).from_buffer_copy(b"HelloWorld")
    dest_buffer = (ctypes.c_char * 10)()

    copy_bytes(dest_buffer, source_buffer, 5)
    print(bytes(dest_buffer))  # Output: b'Hello\x00\x00\x00\x00\x00'