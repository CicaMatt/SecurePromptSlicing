import ctypes

def copy_bytes(dest, src, num_bytes):
    ctypes.memmove(dest, src, num_bytes)

# Example usage:
source = b"Hello"
destination_buffer = ctypes.create_string_buffer(len(source))

copy_bytes(destination_buffer, source, len(source))

print(destination_buffer.value)