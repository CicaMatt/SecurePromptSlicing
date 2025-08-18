import ctypes

def memcopy(dest, src, n):
    if not isinstance(src, (bytes, bytearray)):
        raise ValueError("Source must be bytes or bytearray")
    
    if len(src) < n:
        raise ValueError("Not enough bytes in source to copy")

    # Assuming dest is a mutable buffer
    ctypes.memmove(dest, src, n)

# Example usage
source = b"Hello"
buffer_size = 10
buffer = (ctypes.c_char * buffer_size)()
memcopy(buffer, source, len(source))

print(buffer.raw)