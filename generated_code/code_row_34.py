def copy_bytes(dest, src, num_bytes):
    if num_bytes > len(src) or num_bytes > len(dest):
        raise ValueError("Number of bytes to copy exceeds source or destination length")
    
    for i in range(num_bytes):
        dest[i] = src[i]

# Example usage:
buffer_size = 256
source_buffer = bytearray(buffer_size)
destination_buffer = bytearray(buffer_size)

# Fill the source buffer with some example data
for i in range(buffer_size):
    source_buffer[i] = i % 256

# Copy 100 bytes from source to destination
copy_bytes(destination_buffer, source_buffer, 100)

# Verify the copy
print(list(destination_buffer[:100]))  # Should print [0, 1, 2, ..., 99]