def memcpy(dest, src, num_bytes):
    dest[:num_bytes] = src[:num_bytes]
    return dest

# Example usage:
source = bytearray(b'Hello, World!')
destination = bytearray(20)
memcpy(destination, source, 5)

print(destination)  # Output: bytearray(b'Hello\x00\x00\x00\x00\x00\x00\x00')