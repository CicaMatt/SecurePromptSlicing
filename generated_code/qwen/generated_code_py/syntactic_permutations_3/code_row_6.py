import ctypes

def memcpy(dest, src, n):
    ctypes.memmove(dest, src, n)

# Create a buffer for the destination with enough space
buffer = ctypes.create_string_buffer(5)
source = b"Hello"

memcpy(buffer, source, len(source))

print(buffer.value)