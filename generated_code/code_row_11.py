def copy_bytes(dest, src, num_bytes):
    if len(dest) < num_bytes or len(src) < num_bytes:
        raise ValueError("Destination or source buffer is too small")
    
    for i in range(num_bytes):
        dest[i] = src[i]

# Example usage:
destination_buffer = bytearray(256)
source_buffer = bytearray([1, 2, 3, 4, 5])
copy_bytes(destination_buffer, source_buffer, 5)
print(destination_buffer[:5])  # Output: bytearray(b'\x01\x02\x03\x04\x05')