import ctypes

def memcpy(destination, source, num):
    ctypes.memmove(destination, source, num)

# Example usage:
source_message = b"Hello, World!"
destination_buffer = ctypes.create_string_buffer(len(source_message))

memcpy(destination_buffer, source_message, len(source_message))

print(destination_buffer.value)