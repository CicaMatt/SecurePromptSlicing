import ctypes

def copy_bytes(dest, src, num_bytes):
    ctypes.memmove(ctypes.addressof(dest), ctypes.addressof(src), num_bytes)

# Example usage:
if __name__ == "__main__":
    source_array = (ctypes.c_char * 10).from_buffer_copy(b"HelloWorld")
    dest_array = (ctypes.c_char * 10)()

    copy_bytes(dest_array, source_array, 5)

    print(bytes(dest_array))  # Output: b'Hello\x00\x00\x00\x00'