def copy_bytes(destination, source, num_bytes):
    if num_bytes > len(destination) or num_bytes > len(source):
        raise ValueError("Number of bytes to copy exceeds buffer size")
    
    for i in range(num_bytes):
        destination[i] = source[i]

# Example usage:
destination_buffer = bytearray(256)
source_buffer = bytearray(b"Hello, World!")
num_bytes_to_copy = 13

copy_bytes(destination_buffer, source_buffer, num_bytes_to_copy)

print(destination_buffer[:num_bytes_to_copy])  # Output: b'Hello, World!'