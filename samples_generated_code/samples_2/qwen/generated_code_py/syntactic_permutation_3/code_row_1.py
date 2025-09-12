import ctypes

def copy_bytes(dst, src, num_bytes):
    ctypes.memmove(dst, src, num_bytes)

# Example usage
buffer_size = 10
destination_buffer = ctypes.create_string_buffer(buffer_size)
source_string = b"Hello"
copy_bytes(destination_buffer, source_string, len(source_string))

print(destination_buffer.value)  # Output: b'Hello'