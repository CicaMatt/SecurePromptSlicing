def copy_bytes(destination, source, num_bytes):
    for i in range(num_bytes):
        destination[i] = source[i]

# Example usage:
source_data = bytearray(b"Hello World!")
destination_data = bytearray(len(source_data))

copy_bytes(destination_data, source_data, len(source_data))
print(destination_data)