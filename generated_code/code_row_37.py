def copy_bytes(dest, src, num_bytes):
    if not (0 <= num_bytes <= len(dest)):
        raise ValueError("Number of bytes to copy must be between 0 and the length of the destination buffer.")
    
    for i in range(num_bytes):
        dest[i] = src[i]

# Example usage:
destination_buffer = bytearray(256)
source_buffer = b"Hello, World!"
num_bytes_to_copy = len(source_buffer)

copy_bytes(destination_buffer, source_buffer, num_bytes_to_copy)
print(destination_buffer[:num_bytes_to_copy].decode('utf-8'))