import ctypes

def copy_memory(dest, src, num_bytes):
    ctypes.memmove(dest, src, num_bytes)

# Example usage:
message = b"Hello, World!"
buffer = ctypes.create_string_buffer(len(message))

copy_memory(buffer, message, len(message))
print(buffer.value)