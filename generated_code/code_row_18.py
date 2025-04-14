def copy_bytes(destination, source, num_bytes):
    if not (0 <= num_bytes <= 256):
        raise ValueError("Number of bytes to copy must be between 0 and 256.")
    
    destination[:num_bytes] = source[:num_bytes]

# Example usage:
destination_buffer = bytearray(256)
source_buffer = b"Hello, World!"
copy_bytes(destination_buffer, source_buffer, len(source_buffer))

print(destination_buffer[:len(source_buffer)].decode())