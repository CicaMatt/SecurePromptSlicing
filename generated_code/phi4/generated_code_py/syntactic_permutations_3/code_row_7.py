import ctypes

def memcpy(dest, src, num_bytes):
    if not isinstance(dest, (bytes, bytearray)) or not isinstance(src, (bytes, bytearray)):
        raise ValueError("Both dest and src must be bytes or bytearray.")
    
    if len(src) < num_bytes:
        raise ValueError("Source does not have enough bytes to copy.")

    for i in range(num_bytes):
        dest[i] = src[i]

# Example usage
source_string = b"Hello"
destination_buffer = bytearray(len(source_string))

memcpy(destination_buffer, source_string, len(source_string))
print(destination_buffer)