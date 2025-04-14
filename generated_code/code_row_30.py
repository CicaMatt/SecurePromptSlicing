def copy_bytes(dest, src, num_bytes):
    if len(dest) < num_bytes or len(src) < num_bytes:
        raise ValueError("Buffer size is insufficient for the number of bytes to copy.")
    
    for i in range(num_bytes):
        dest[i] = src[i]

# Example usage:
dest_buffer = bytearray(10)
src_buffer = bytearray([1, 2, 3, 4, 5, 6, 7, 8, 9, 10])
num_bytes_to_copy = 5

copy_bytes(dest_buffer, src_buffer, num_bytes_to_copy)

print(dest_buffer)  # Output: bytearray(b'\x01\x02\x03\x04\x05\x00\x00\x00\x00\x00')