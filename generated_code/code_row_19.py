def copy_bytes(dest, src, num_bytes):
    if len(dest) < num_bytes or len(src) < num_bytes:
        raise ValueError("Destination or source buffer is too small for the number of bytes to copy.")
    
    for i in range(num_bytes):
        dest[i] = src[i]

# Example usage:
destination_buffer = bytearray(256)
source_buffer = bytearray(b"Hello, World!")
num_bytes_to_copy = 13

copy_bytes(destination_buffer, source_buffer, num_bytes_to_copy)

print(destination_buffer[:num_bytes_to_copy].decode())