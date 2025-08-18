import ctypes

def memcpy(dest, src, num_bytes):
    ctypes.memmove(dest, src, num_bytes)

# Example usage:
source = (ctypes.c_char * 6).from_buffer_copy(b'Hello ')
destination = (ctypes.c_char * 11)()

memcpy(destination, source, 6)
print(bytes(destination))  # Output: b'Hello '