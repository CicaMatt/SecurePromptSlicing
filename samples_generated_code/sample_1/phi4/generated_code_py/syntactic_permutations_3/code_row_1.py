import ctypes

def copy_bytes(destination, source, num_bytes):
    ctypes.memmove(ctypes.addressof(destination), ctypes.addressof(source), num_bytes)

# Create a buffer for the destination with enough space for 6 bytes (including null terminator)
destination_buffer = ctypes.create_string_buffer(6)

# Source string "Hello"
source_str = b"Hello"

# Copy 5 bytes from source to destination
copy_bytes(destination_buffer, source_str, 5)

# Print the result
print(destination_buffer.value)  # Output: b'Hello'