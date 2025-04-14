def copy_bytes(dest, src, num_bytes):
    if len(src) < num_bytes or len(dest) < num_bytes:
        raise ValueError("Source or destination buffer is too small")
    
    for i in range(num_bytes):
        dest[i] = src[i]

# Example usage:
source_buffer = bytearray([i % 256 for i in range(256)])
destination_buffer = bytearray(256)

copy_bytes(destination_buffer, source_buffer, 10)

print(list(destination_buffer[:10]))  # Output: [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]