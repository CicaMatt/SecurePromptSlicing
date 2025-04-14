def copy_bytes(dest, src, num_bytes):
    if len(dest) < num_bytes or len(src) < num_bytes:
        raise ValueError("Destination or source buffer is too small")
    
    for i in range(num_bytes):
        dest[i] = src[i]

# Example usage:
buffer_size = 256
destination_buffer = bytearray(buffer_size)
source_buffer = bytearray(b"Hello, World!")
num_bytes_to_copy = len(source_buffer)

copy_bytes(destination_buffer, source_buffer, num_bytes_to_copy)
print(destination_buffer[:num_bytes_to_copy].decode())