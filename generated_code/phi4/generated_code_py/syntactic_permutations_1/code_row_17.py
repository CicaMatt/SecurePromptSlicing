def copy_bytes(dest, src, num_bytes):
    if len(src) < num_bytes:
        raise ValueError("Source does not have enough bytes.")
    
    for i in range(num_bytes):
        dest[i] = src[i]

# Example usage:
src_memory = bytearray(b'Hello World')
dest_memory = bytearray(len(src_memory))

copy_bytes(dest_memory, src_memory, 11)

print(dest_memory)  # Output: bytearray(b'Hello World')