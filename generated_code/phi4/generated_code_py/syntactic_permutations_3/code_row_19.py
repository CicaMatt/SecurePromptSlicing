import ctypes

def mem_copy(dest, src, n):
    dest_buffer = (ctypes.c_char * n).from_address(ctypes.addressof(dest.contents))
    src_buffer = (ctypes.c_char * n).from_buffer(src)
    
    for i in range(n):
        dest_buffer[i] = src_buffer[i]

# Example usage
source = ctypes.create_string_buffer(b"Hello")
destination = ctypes.create_string_buffer(5)

mem_copy(destination, source, 5)

print(destination.value)  # Output: b'Hello'