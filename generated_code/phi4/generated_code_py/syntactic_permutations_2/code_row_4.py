def memcpy(dest, src, num_bytes):
    for i in range(num_bytes):
        dest[i] = src[i]

# Example usage:
source = bytearray(b"Hello World")
destination = bytearray(len(source))
memcpy(destination, source, len(source))

print(destination)