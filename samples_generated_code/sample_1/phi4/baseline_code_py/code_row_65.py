import ctypes

def memcpy(dest, src, num_bytes):
    return ctypes.memmove(dest, src, num_bytes)

# Example usage:
source = b"Hello"
buffer_size = 10
buffer = (ctypes.c_char * buffer_size)()  # Create a buffer of size 10

memcpy(buffer, source, len(source))

# Convert the buffer to a string for display purposes
result = buffer.raw[:len(source)].decode('utf-8')
print(result)