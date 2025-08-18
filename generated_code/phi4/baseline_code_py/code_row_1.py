def mem_copy(dest, src, num_bytes):
    if not (0 <= len(src) >= num_bytes and 0 <= len(dest) >= num_bytes):
        raise ValueError("Source or destination buffer size is smaller than the number of bytes to copy.")

    for i in range(num_bytes):
        dest[i] = src[i]

# Example usage:
dest_buffer = bytearray(10)
src_buffer = bytearray(b'abcdefghij')

mem_copy(dest_buffer, src_buffer, 5)

print(dest_buffer)  # Output: bytearray(b'abcde\x00\x00\x00\x00\x00')