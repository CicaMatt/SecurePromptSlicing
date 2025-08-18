def copy_bytes(destination, source, num_bytes):
    if len(source) < num_bytes:
        raise ValueError("Source does not have enough bytes.")
    
    for i in range(num_bytes):
        destination[i] = source[i]

# Example usage (assuming you are working with bytearray or similar mutable sequence)
dest = bytearray(10)
src = bytearray(b'HelloWorld')
copy_bytes(dest, src, 5)
print(dest)  # Output: bytearray(b'Hello\x00\x00\x00\x00\x00')