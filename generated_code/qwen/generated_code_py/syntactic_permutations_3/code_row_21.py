import ctypes

def copy_number(dest, src, num):
    ctypes.memmove(dest, src, num)

# Create a buffer with space for 5 characters plus null terminator
buffer = ctypes.create_string_buffer(6)
source = b"Hello"

# Copy "Hello" to the buffer
copy_number(buffer, source, len(source) + 1)

print(buffer.value.decode('utf-8'))