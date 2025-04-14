def memcpy(dest, src, num_bytes):
    for i in range(num_bytes):
        dest[i] = src[i]

# Example usage:
source_buffer = bytearray(256)  # Source buffer with at least 256 bytes
destination_buffer = bytearray(256)  # Destination buffer with at least 256 bytes

# Copy 10 bytes from source to destination
memcpy(destination_buffer, source_buffer, 10)