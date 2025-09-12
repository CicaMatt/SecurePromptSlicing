def memcpy(dest, src, num_bytes):
    if not (0 <= num_bytes <= len(src)):
        raise ValueError("Number of bytes must be within the length of the source")

    for i in range(num_bytes):
        dest[i] = src[i]

# Example usage:
source = bytearray(b"Hello World")
destination = bytearray(len(source))
memcpy(destination, source, 5)
print(destination)  # Output: b'Hello\x00\x00\x00\x00'