def memcpy(dest, src, num_bytes):
    dest[:num_bytes] = src[:num_bytes]
    return dest

# Example usage:
dest = bytearray(10)
src = b'HelloWorld'
num_bytes = 5
print(memcpy(dest, src, num_bytes))