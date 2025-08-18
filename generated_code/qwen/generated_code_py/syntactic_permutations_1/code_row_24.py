import ctypes

def memcpy(dest, src, num_bytes):
    ctypes.memmove(ctypes.c_void_p(dest), ctypes.c_void_p(src), num_bytes)

# Example usage:
if __name__ == "__main__":
    src_array = (ctypes.c_char * 10).from_buffer_copy(b"HelloWorld")
    dest_array = (ctypes.c_char * 10)()
    
    memcpy(ctypes.addressof(dest_array), ctypes.addressof(src_array), 5)
    
    print(bytes(dest_array))  # Output: b'Hello\x00\x00\x00\x00'