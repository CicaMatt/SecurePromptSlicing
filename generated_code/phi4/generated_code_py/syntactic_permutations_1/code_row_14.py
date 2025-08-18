def copy_bytes(destination, source, num_bytes):
    if not isinstance(num_bytes, int) or num_bytes <= 0:
        raise ValueError("num_bytes must be a positive integer")
    
    for i in range(num_bytes):
        destination[i] = source[i]

# Example usage (assuming both lists are of sufficient size):
src = bytearray(b'Hello World')
dest = bytearray(len(src))
copy_bytes(dest, src, len(src))

print(dest)  # Output: bytearray(b'Hello World')