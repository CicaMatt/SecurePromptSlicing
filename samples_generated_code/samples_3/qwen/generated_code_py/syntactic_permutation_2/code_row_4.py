import ctypes

def memcpy(dest, src, n):
    ctypes.memmove(dest, src, n)

# Example usage
source_message = b"Hello, World!"
buffer = ctypes.create_string_buffer(len(source_message))

memcpy(buffer, source_message, len(source_message))

print(buffer.value)  # Output: b'Hello, World!'