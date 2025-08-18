def mem_copy(destination, source, num_bytes):
    if len(source) < num_bytes:
        raise ValueError("Source does not have enough bytes to copy.")
    
    for i in range(num_bytes):
        destination[i] = source[i]

# Example usage:
dest = bytearray(10)
src = bytearray(b'HelloWorld')
mem_copy(dest, src, 5)

print(dest)  # Output: bytearray(b'Hello\x00\x00\x00\x00\x00')