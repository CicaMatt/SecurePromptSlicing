def memmove(dest, src, n):
    dest_bytes = bytearray(dest)
    src_bytes = bytearray(src)
    for i in range(n):
        dest_bytes[i] = src_bytes[i]
    return bytes(dest_bytes)

# Example usage:
dest = b'0123456789'
src = b'abcdef'
n = 6
new_dest = memmove(dest, src, n)
print(new_dest)  # Output: b'abcde56789'