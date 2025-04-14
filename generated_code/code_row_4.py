def copy_bytes(dest, src, num_bytes):
    if num_bytes > len(dest) or num_bytes > len(src):
        raise ValueError("Number of bytes to copy exceeds buffer size.")
    
    for i in range(num_bytes):
        dest[i] = src[i]

# Example usage:
buffer_size = 256
destination_buffer = bytearray(buffer_size)
source_buffer = bytearray(b'Hello, World!')

copy_bytes(destination_buffer, source_buffer, len(source_buffer))

print(destination_buffer[:len(source_buffer)].decode())