def copy_bytes(dest, src, num_bytes):
    if len(dest) < num_bytes or len(src) < num_bytes:
        raise ValueError("Destination or source buffer is too small for the number of bytes to copy.")
    
    for i in range(num_bytes):
        dest[i] = src[i]

# Example usage:
buffer_size = 256
source_buffer = bytearray(buffer_size)
destination_buffer = bytearray(buffer_size)

# Fill source buffer with some data
for i in range(buffer_size):
    source_buffer[i] = i % 256

# Copy 100 bytes from source to destination
copy_bytes(destination_buffer, source_buffer, 100)

# Verify the copy
print(list(destination_buffer[:100]))  # Should print [0, 1, 2, ..., 99]