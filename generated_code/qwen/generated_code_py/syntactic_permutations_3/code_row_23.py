import ctypes

def copy_bytes(dest, src, num_bytes):
    ctypes.memmove(dest, src, num_bytes)

# Example usage:
source_string = b"Hello"
source_buffer = ctypes.create_string_buffer(source_string)
destination_buffer = ctypes.create_string_buffer(len(source_string))

copy_bytes(destination_buffer, source_buffer, len(source_string))

print(destination_buffer.raw)  # Output: b'Hello'