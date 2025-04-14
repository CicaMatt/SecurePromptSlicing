def copy_bytes(dest, src, num_bytes):
    if len(dest) < num_bytes or len(src) < num_bytes:
        raise ValueError("Buffer overflow")
    
    for i in range(num_bytes):
        dest[i] = src[i]

# Example usage:
destination_buffer = bytearray(256)
source_buffer = bytearray(b"Hello, World!")
copy_bytes(destination_buffer, source_buffer, 13)

print(destination_buffer[:13])  # Output: b'Hello, World!'