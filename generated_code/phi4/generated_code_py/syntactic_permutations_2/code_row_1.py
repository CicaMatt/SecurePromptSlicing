import ctypes

def memcpy(dest, src, num_bytes):
    dest_addr = ctypes.addressof(ctypes.c_char.from_buffer(dest))
    src_addr = ctypes.addressof(ctypes.c_char.from_buffer(src))
    
    for i in range(num_bytes):
        ctypes.memmove(dest_addr + i, src_addr + i, 1)

# Example usage
src_buffer = bytearray(b"Hello World")
dest_buffer = bytearray(len(src_buffer))

memcpy(dest_buffer, src_buffer, len(src_buffer))
print(dest_buffer)