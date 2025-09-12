import ctypes

def memcpy(dest, src, num):
    ctypes.memmove(dest, src, num)

# Example usage:
if __name__ == "__main__":
    src_buffer = (ctypes.c_char * 10).from_buffer_copy(b"HelloWorld")
    dest_buffer = (ctypes.c_char * 10)()
    
    memcpy(ctypes.addressof(dest_buffer), ctypes.addressof(src_buffer), 5)
    
    print(bytes(dest_buffer))  # Output: b'Hello\x00\x00\x00\x00\x00'