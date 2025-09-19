import ctypes

def memcpy(dest, src, n):
    ctypes.memmove(dest, src, n)

# Create a buffer with space for 5 characters plus the null terminator
buffer = ctypes.create_string_buffer(6)
source = b"Hello"

memcpy(buffer, source, len(source))

print(buffer.value.decode('utf-8'))