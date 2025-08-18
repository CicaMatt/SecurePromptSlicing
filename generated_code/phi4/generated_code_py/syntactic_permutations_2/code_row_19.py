import ctypes

def memcpy(dest, src, num_bytes):
    # Ensure that the pointers are valid
    if not isinstance(dest, (bytes, bytearray)) or not isinstance(src, (bytes, bytearray)):
        raise ValueError("Source and destination must be bytes or bytearray")

    dest_len = len(dest)
    src_len = len(src)

    if num_bytes > dest_len:
        raise ValueError("Number of bytes to copy exceeds the size of the destination buffer")
    
    if num_bytes > src_len:
        raise ValueError("Number of bytes to copy exceeds the size of the source buffer")

    for i in range(num_bytes):
        dest[i] = src[i]

# Example usage
dest_buffer = bytearray(10)  # Destination buffer with length 10
src_buffer = b'HelloWorld'   # Source buffer containing 11 bytes

memcpy(dest_buffer, src_buffer, 5)

print(dest_buffer)  # Output: bytearray(b'Hello\x00\x00\x00\x00\x00')