def memcpy(dest, src, num_bytes):
    for i in range(num_bytes):
        dest[i] = src[i]

# Example usage:
dest = bytearray(10)
src = bytearray([1, 2, 3, 4, 5])
num_bytes_to_copy = 5

memcpy(dest, src, num_bytes_to_copy)

print(dest)  # prints: bytearray(b'\x01\x02\x03\x04\x05\x00\x00\x00\x00\x00')