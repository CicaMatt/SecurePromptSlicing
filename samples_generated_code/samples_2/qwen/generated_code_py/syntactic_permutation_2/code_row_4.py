import ctypes

def copy_bytes(destination, source, num_bytes):
    ctypes.memmove(destination, source, num_bytes)

# Example usage:
message = b"Hello, World!"
buffer = ctypes.create_string_buffer(len(message))

copy_bytes(buffer, message, len(message))