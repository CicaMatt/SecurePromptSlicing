import ctypes

def memcpy(dest, src, n):
    ctypes.memmove(dest, src, n)

# Create a buffer with space for 6 characters (5 for "Hello" and 1 for null terminator)
buffer = ctypes.create_string_buffer(6)

# Source string
source = b"Hello"

# Copy the string from source to buffer
memcpy(buffer, source, len(source))

# Convert buffer to string to display
result = buffer.value.decode('utf-8')
print(result)