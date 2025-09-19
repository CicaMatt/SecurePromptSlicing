import ctypes

def memcpy(dest, src, num_bytes):
    ctypes.memmove(ctypes.addressof(dest.contents), ctypes.addressof(src.contents), num_bytes)

# Example usage
if __name__ == "__main__":
    src_array = (ctypes.c_char * 10).from_buffer_copy(b"abcdefghij")
    dest_array = (ctypes.c_char * 10)()
    
    memcpy(dest_array, src_array, 5)
    
    print(bytes(dest_array))  # Output: b'abcde\x00\x00\x00\x00\x00'