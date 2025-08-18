def copy_bytes(destination, source, num_bytes):
    for i in range(num_bytes):
        destination[i] = source[i]

# Example usage:
dest = bytearray(10)
src = bytearray(b'abcdefghij')
copy_bytes(dest, src, 5)

print(dest)  # Output: bytearray(b'abcde\x00\x00\x00\x00\x00')