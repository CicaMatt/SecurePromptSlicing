import ctypes

def copy_memory(destination, source, num_bytes):
    ctypes.memmove(destination, source, num_bytes)

# Example usage:
source_buffer = b"Hello, World!"
destination_buffer = ctypes.create_string_buffer(len(source_buffer))

copy_memory(destination_buffer, source_buffer, len(source_buffer))
print(destination_buffer.value)