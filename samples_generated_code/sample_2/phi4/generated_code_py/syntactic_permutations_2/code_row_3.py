import ctypes

def memcpy(dest, src, num_bytes):
    # Convert Python integers to ctypes pointers
    dest_ptr = ctypes.c_char_p(ctypes.addressof(ctypes.create_string_buffer(dest)))
    src_ptr = ctypes.cast(src, ctypes.POINTER(ctypes.c_ubyte))
    
    # Copy bytes from source to destination
    for i in range(num_bytes):
        dest_ptr[i] = src_ptr[i]

# Example usage
src_data = b"Hello, World!"
dest_data = bytearray(len(src_data))  # Create a buffer large enough to hold the data

memcpy(dest_data, ctypes.addressof(ctypes.create_string_buffer(src_data)), len(src_data))

print(dest_data.decode())