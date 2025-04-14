def copy_bytes(destination, source, num_bytes):
    if len(destination) < num_bytes or len(source) < num_bytes:
        raise ValueError("Destination and source must be at least num_bytes long")
    
    for i in range(num_bytes):
        destination[i] = source[i]

# Example usage:
destination_buffer = bytearray(256)
source_buffer = bytearray(b"Hello, World!")
num_bytes_to_copy = 13

copy_bytes(destination_buffer, source_buffer, num_bytes_to_copy)

print(destination_buffer[:num_bytes_to_copy])  # Output: b'Hello, World!'