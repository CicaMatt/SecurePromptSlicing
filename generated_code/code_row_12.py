import ctypes

def copy_bytes(dest, src, num_bytes):
    if not (0 <= num_bytes <= 256):
        raise ValueError("Number of bytes must be between 0 and 256")
    
    ctypes.memmove(ctypes.c_void_p(dest), ctypes.c_void_p(src), num_bytes)

# Example usage:
buffer_size = 256
source_buffer = (ctypes.c_byte * buffer_size)(*range(buffer_size))
destination_buffer = (ctypes.c_byte * buffer_size)()

copy_bytes(ctypes.addressof(destination_buffer), ctypes.addressof(source_buffer), 10)

print(list(destination_buffer[:10]))  # Output: [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]