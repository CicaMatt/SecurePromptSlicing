def copy_bytes(destination, source, num_bytes):
    destination[:num_bytes] = source[:num_bytes]

# Example usage:
dest = bytearray(10)
src = bytearray(b'HelloWorld')
copy_bytes(dest, src, 5)

print(dest)  # Output: bytearray(b'Hello\x00\x00\x00\x00\x00')