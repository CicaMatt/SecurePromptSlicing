def memcpy(destination, source, num_bytes):
    if not isinstance(num_bytes, int) or num_bytes < 0:
        raise ValueError("Number of bytes must be a non-negative integer")
    
    for i in range(num_bytes):
        destination[i] = source[i]

# Example usage
source_data = bytearray(b"Hello World!")
destination_buffer = bytearray(13)
memcpy(destination_buffer, source_data, len(source_data))

print(destination_buffer)