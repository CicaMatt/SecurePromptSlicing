def copy_bytes(destination, source, num_bytes):
    if not (0 <= num_bytes <= len(source)):
        raise ValueError("num_bytes must be within the range of the source length.")
    
    destination[:num_bytes] = source[:num_bytes]

# Example usage:
source_data = bytearray(b"Hello World")
destination_buffer = bytearray(len(source_data))
copy_bytes(destination_buffer, source_data, 5)

print(destination_buffer)