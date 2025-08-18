def mem_copy(dest, src, num_bytes):
    for i in range(num_bytes):
        dest[i] = src[i]

# Example usage:
src_buffer = bytearray(b"Hello World")
dest_buffer = bytearray(len(src_buffer))

mem_copy(dest_buffer, src_buffer, len(src_buffer))
print(dest_buffer)