import ctypes

def copy_bytes(destination, source, num_bytes):
    ctypes.memmove(destination, source, num_bytes)

# Example usage:
source_buffer = ctypes.create_string_buffer(b"Hello")
destination_buffer = ctypes.create_string_buffer(5)
copy_bytes(ctypes.addressof(destination_buffer), ctypes.addressof(source_buffer), 5)

print(destination_buffer.raw)  # Output: b'Hello'