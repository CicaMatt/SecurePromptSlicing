def memcpy(dest, src, num_bytes):
    if not (0 <= num_bytes <= len(src) and 0 <= num_bytes <= len(dest)):
        raise ValueError("num_bytes exceeds the length of source or destination")
    
    for i in range(num_bytes):
        dest[i] = src[i]

# Example usage:
dest_array = bytearray(10)
src_array = bytearray(b'hello1234')
memcpy(dest_array, src_array, 7)

print(dest_array)  # Output: bytearray(b'hello123\x00\x00\x00\x00')