import ctypes

def memcopy(dest, src, nbytes):
    ctypes.memmove(dest, src, nbytes)

# Example usage
buffer = (ctypes.c_char * 6)()  # Create a buffer for 6 bytes
source = b"Hello"
memcopy(buffer, source, len(source))

print(buffer.raw)