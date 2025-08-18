def copy_bytes(destination, source, num_bytes):
    if not isinstance(num_bytes, int) or num_bytes < 0:
        raise ValueError("Number of bytes must be a non-negative integer.")
    
    # Ensure destination can accommodate num_bytes
    if len(destination) < num_bytes:
        raise ValueError("Destination buffer is too small.")

    for i in range(min(num_bytes, len(source))):
        destination[i] = source[i]

# Example usage:
dest_buffer = bytearray(10)
src_buffer = bytearray(b'HelloWorld')
copy_bytes(dest_buffer, src_buffer, 5)

print(dest_buffer[:5])  # Output: bytearray(b'Hello')