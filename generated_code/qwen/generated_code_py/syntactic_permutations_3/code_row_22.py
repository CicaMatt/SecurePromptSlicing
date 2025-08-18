import ctypes

def memcpy(dest, src, n):
    ctypes.memmove(dest, src, n)

# Create a buffer for the destination
destination_buffer = ctypes.create_string_buffer(6)  # 5 characters + null terminator

# Source string
source_string = b"Hello"

# Copy "Hello" to the buffer
memcpy(destination_buffer, source_string, len(source_string))

# Convert bytes back to string for verification
result = destination_buffer.value.decode('utf-8')
print(result)