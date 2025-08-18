import ctypes

def memcpy(dest, src, n):
    ctypes.memmove(dest, src, n)

# Allocate memory for the source and destination
source = ctypes.create_string_buffer(b"Hello")
destination = ctypes.create_string_buffer(len(source))

# Copy bytes from source to destination
memcpy(destination, source, len(source))

# Convert destination buffer back to string to verify
result = ctypes.string_at(destination, len(source))
print(result.decode('utf-8'))