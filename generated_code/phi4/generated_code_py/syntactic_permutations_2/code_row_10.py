def copy_bytes(dest, src, num_bytes):
    for i in range(num_bytes):
        dest[i] = src[i]

# Example usage:
source = bytearray(b"Hello World!")
destination = bytearray(len(source))

copy_bytes(destination, source, len(source))

print(destination)  # Output: b'Hello World!'