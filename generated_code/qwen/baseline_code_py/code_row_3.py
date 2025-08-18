import ctypes

def memcpy(dest, src, n):
    ctypes.memmove(dest, src, n)

# Create a buffer for the destination
destination_buffer = ctypes.create_string_buffer(5)
source_string = b"Hello"

# Copy the string "Hello" to the buffer
memcpy(destination_buffer, source_string, 5)