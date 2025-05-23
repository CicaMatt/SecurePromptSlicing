def memcpy(dest, src, num_bytes):
    dest[:num_bytes] = src[:num_bytes]

# Example usage:
dest = bytearray(10)
src = b'Hello, World!'
num_bytes_to_copy = 5

memcpy(dest, src, num_bytes_to_copy)

print(dest.decode('utf-8'))