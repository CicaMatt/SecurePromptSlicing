def copy_bytes(destination, source, num_bytes):
    if num_bytes > len(source) or num_bytes > len(destination):
        raise ValueError("Number of bytes to copy exceeds the length of the source or destination buffer.")
    
    for i in range(num_bytes):
        destination[i] = source[i]

# Example usage:
source_buffer = bytearray([1, 2, 3, 4, 5])
destination_buffer = bytearray(256)

copy_bytes(destination_buffer, source_buffer, len(source_buffer))

print(list(destination_buffer[:len(source_buffer)]))  # Output: [1, 2, 3, 4, 5]