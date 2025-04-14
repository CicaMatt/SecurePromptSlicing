import ctypes

def copy_bytes(destination, source, num_bytes):
    if num_bytes > 256:
        raise ValueError("Number of bytes exceeds buffer size (256)")
    
    # Ensure destination and source are pointers to memory
    dest_ptr = ctypes.cast(destination, ctypes.POINTER(ctypes.c_ubyte))
    src_ptr = ctypes.cast(source, ctypes.POINTER(ctypes.c_ubyte))
    
    # Copy the specified number of bytes
    for i in range(num_bytes):
        dest_ptr[i] = src_ptr[i]

# Example usage:
buffer_size = 256
source_buffer = (ctypes.c_ubyte * buffer_size)()
destination_buffer = (ctypes.c_ubyte * buffer_size)()

# Fill source buffer with some data
for i in range(10):
    source_buffer[i] = i

# Copy 10 bytes from source to destination
copy_bytes(destination_buffer, source_buffer, 10)

# Verify the copy
for i in range(10):
    print(destination_buffer[i])  # Output should be 0, 1, 2, ..., 9