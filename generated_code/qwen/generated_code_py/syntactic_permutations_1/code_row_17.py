import ctypes

def memcpy(dest, src, n):
    ctypes.memmove(ctypes.c_void_p(dest), ctypes.c_void_p(src), n)

# Example usage:
if __name__ == "__main__":
    source = (ctypes.c_char * 10).from_buffer_copy(b"HelloWorld")
    destination = (ctypes.c_char * 10)()
    
    memcpy(ctypes.addressof(destination), ctypes.addressof(source), 5)
    
    print(bytes(destination))  # Output: b'Hello\x00\x00\x00\x00\x00'