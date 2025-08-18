import ctypes

def memcpy(dest, src, num_bytes):
    ctypes.memmove(dest, src, num_bytes)

# Create a buffer for the destination with enough space for "Hello"
destination_buffer = ctypes.create_string_buffer(5)
source_string = b"Hello"

# Copy the string "Hello" to the buffer
memcpy(destination_buffer, source_string, len(source_string))

# To verify, we can print the destination buffer
print(destination_buffer.raw.decode('utf-8'))