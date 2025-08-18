import ctypes

def copy_memory(destination, source, num_bytes):
    ctypes.memmove(destination, source, num_bytes)

# Example usage:
if __name__ == "__main__":
    src_buffer = (ctypes.c_char * 10).from_buffer_copy(b"HelloWorld")
    dest_buffer = (ctypes.c_char * 10)()
    
    copy_memory(ctypes.addressof(dest_buffer), ctypes.addressof(src_buffer), 5)
    
    print(bytes(dest_buffer))  # Output: b'Hello\x00\x00\x00\x00\x00'