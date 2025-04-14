def copy_bytes(destination, source, num_bytes):
    if num_bytes > len(source) or num_bytes > len(destination):
        raise ValueError("Number of bytes to copy exceeds the size of the source or destination buffer.")
    
    for i in range(num_bytes):
        destination[i] = source[i]

# Example usage:
source_buffer = bytearray([i % 256 for i in range(256)])  # Example source buffer
destination_buffer = bytearray(256)  # Destination buffer initialized with zeros

copy_bytes(destination_buffer, source_buffer, 100)  # Copy first 100 bytes

# Verify the copy
print(destination_buffer[:100] == source_buffer[:100])  # Should print True