def copy_bytes(dest, src, num_bytes):
    if num_bytes > len(dest) or num_bytes > len(src):
        raise ValueError("Number of bytes exceeds the size of the destination or source buffer")
    
    dest[:num_bytes] = src[:num_bytes]

# Example usage:
destination_buffer = bytearray(256)
source_buffer = bytearray(b"Hello, World!")
copy_bytes(destination_buffer, source_buffer, 13)

print(destination_buffer[:13])  # Output: b'Hello, World!'