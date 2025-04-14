def copy_bytes(destination, source, num_bytes):
    if num_bytes > len(source) or num_bytes > len(destination):
        raise ValueError("Number of bytes to copy exceeds the length of the source or destination buffer.")
    
    for i in range(num_bytes):
        destination[i] = source[i]

# Example usage:
source_buffer = bytearray(b'Hello, World!')
destination_buffer = bytearray(256)  # Buffer is 256 bytes long

copy_bytes(destination_buffer, source_buffer, len(source_buffer))

print(destination_buffer[:len(source_buffer)])  # Output: b'Hello, World!'