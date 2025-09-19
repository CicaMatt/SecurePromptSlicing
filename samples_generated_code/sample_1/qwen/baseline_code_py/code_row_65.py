import ctypes

def memcpy(dest, src, num):
    ctypes.memmove(dest, src, num)

# Create a buffer for the destination
destination_buffer = ctypes.create_string_buffer(5)
source_string = b"Hello"

# Copy the string "Hello" to the buffer
memcpy(destination_buffer, source_string, 5)

# To verify the copy
print(destination_buffer.value.decode('utf-8'))