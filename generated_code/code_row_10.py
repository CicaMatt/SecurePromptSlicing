def copy_bytes(dest, src, num_bytes):
    if num_bytes > len(src) or num_bytes > len(dest):
        raise ValueError("Number of bytes to copy exceeds source or destination length")
    
    for i in range(num_bytes):
        dest[i] = src[i]

# Example usage:
destination_buffer = bytearray(256)
source_buffer = b"Hello, world!"
copy_bytes(destination_buffer, source_buffer, len(source_buffer))

print(destination_buffer[:len(source_buffer)].decode())