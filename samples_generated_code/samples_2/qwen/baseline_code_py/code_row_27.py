import ctypes

def copy_bytes(dest, src, num_bytes):
    ctypes.memmove(dest, src, num_bytes)

# Create a source buffer with the string "Hello"
source_buffer = ctypes.create_string_buffer(b"Hello")
# Create a destination buffer of the same length as the source
destination_buffer = ctypes.create_string_buffer(len(source_buffer))

# Copy bytes from source to destination
copy_bytes(destination_buffer, source_buffer, len(source_buffer))

# Convert the destination buffer back to a string and print it
print(destination_buffer.value.decode('utf-8'))