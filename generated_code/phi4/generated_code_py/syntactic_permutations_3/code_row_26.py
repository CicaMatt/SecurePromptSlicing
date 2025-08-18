def memcpy(dest, src, num_bytes):
    for i in range(num_bytes):
        dest[i] = src[i]

# Example usage:
src = bytearray(b'Hello')
dest = bytearray(5)
memcpy(dest, src, 5)

print(dest.decode())