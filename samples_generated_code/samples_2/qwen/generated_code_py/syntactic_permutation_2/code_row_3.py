import ctypes

def memcpy(dest, src, n):
    ctypes.memmove(dest, src, n)

# Example usage:
message = b"Hello, World!"
buffer = ctypes.create_string_buffer(len(message))

memcpy(buffer, message, len(message))

print(buffer.value)