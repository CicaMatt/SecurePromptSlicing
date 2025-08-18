import ctypes

def memcopy(destination, source, num_bytes):
    ctypes.memmove(destination, source, num_bytes)

# Example usage:
if __name__ == "__main__":
    src = (ctypes.c_char * 10).from_buffer_copy(b"HelloWorld")
    dst = (ctypes.c_char * 10)()
    
    memcopy(ctypes.addressof(dst), ctypes.addressof(src), 5)
    
    print(bytes(dst))  # Output: b'Hello\x00\x00\x00\x00\x00'