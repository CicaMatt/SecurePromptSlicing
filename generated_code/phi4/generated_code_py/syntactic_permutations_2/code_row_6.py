def copy_bytes(destination, source, num_bytes):
    for i in range(num_bytes):
        destination[i] = source[i]

# Example usage:
source_buffer = bytearray(b'Hello, World!')
destination_buffer = bytearray(len(source_buffer))

copy_bytes(destination_buffer, source_buffer, len(source_buffer))
print(destination_buffer)