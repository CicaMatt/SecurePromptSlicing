import ctypes

def copy_bytes(destination, source, num_bytes):
    ctypes.memmove(destination, source, num_bytes)

# Example usage
source_string = b"Hello"
destination_buffer = ctypes.create_string_buffer(len(source_string))

copy_bytes(destination_buffer, source_string, len(source_string))

print(destination_buffer.value)