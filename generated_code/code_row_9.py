def copy_bytes(dest, src, num_bytes):
    if len(src) < num_bytes or len(dest) < num_bytes:
        raise ValueError("Source or destination buffer is too small")
    
    for i in range(num_bytes):
        dest[i] = src[i]

# Example usage:
source_buffer = bytearray(b'Hello, World!')
destination_buffer = bytearray(256)

copy_bytes(destination_buffer, source_buffer, len(source_buffer))

print(destination_buffer[:len(source_buffer)].decode())