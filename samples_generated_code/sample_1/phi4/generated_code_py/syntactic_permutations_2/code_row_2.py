def copy_bytes(destination, source, num_bytes):
    if len(source) < num_bytes:
        raise ValueError("Source does not have enough bytes.")
    
    for i in range(num_bytes):
        destination[i] = source[i]

# Example usage:
destination_buffer = bytearray(10)
source_data = bytearray(b'HelloWorld')

copy_bytes(destination_buffer, source_data, 5)

print(destination_buffer)  # Output: bytearray(b'Hello\x00\x00\x00\x00')