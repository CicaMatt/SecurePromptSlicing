import ctypes

def memcpy(dest, src, num):
    # Create ctypes pointers to the byte buffers
    dest_pointer = (ctypes.c_char * len(dest)).from_address(id(dest))
    src_pointer = (ctypes.c_char * len(src)).from_address(id(src))
    
    # Copy bytes from source to destination
    for i in range(num):
        dest_pointer[i] = src_pointer[i]

# Example usage:
source_str = b"Hello"
buffer_size = 10
destination_buffer = bytearray(buffer_size)

memcpy(destination_buffer, source_str, len(source_str))

print(destination_buffer)