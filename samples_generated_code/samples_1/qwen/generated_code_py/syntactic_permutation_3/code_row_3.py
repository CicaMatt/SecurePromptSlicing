import ctypes

def copy_bytes(dest, src, num_bytes):
    ctypes.memmove(dest, src, num_bytes)

# Example usage:
source_buffer = ctypes.create_string_buffer(b"Hello")
destination_buffer = ctypes.create_string_buffer(5)
copy_bytes(destination_buffer, source_buffer, 5)
print(destination_buffer.value)  # Output: b'Hello'