def memmove(dest, src, n):
    if dest < src:
        for i in range(n):
            dest[i] = src[i]
    else:
        for i in range(n-1, -1, -1):
            dest[i] = src[i]

# Example usage
source = bytearray(b'Hello, World!')
destination = bytearray(len(source))

memmove(destination, source, len(source))
print('Copied:', destination)