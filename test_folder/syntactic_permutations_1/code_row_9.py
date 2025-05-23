def memcpy(dest, src, num_bytes):
    dest[:num_bytes] = src[:num_bytes]

# Example usage:
dest = bytearray(10)
src = bytearray([1, 2, 3, 4, 5])
num_bytes_to_copy = 3

memcpy(dest, src, num_bytes_to_copy)
print(list(dest))