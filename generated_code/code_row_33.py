import ctypes

def copy_bytes(dest, src, num_bytes):
    if num_bytes > len(dest) or num_bytes > len(src):
        raise ValueError("Number of bytes to copy exceeds buffer size")
    
    ctypes.memmove(ctypes.addressof(dest), ctypes.addressof(src), num_bytes)

# Example usage:
buffer_size = 256
source_buffer = (ctypes.c_char * buffer_size)()
destination_buffer = (ctypes.c_char * buffer_size)()

# Fill source buffer with some data
message = b"Hello, World!"
ctypes.memmove(ctypes.addressof(source_buffer), message, len(message))

# Copy bytes from source to destination
copy_bytes(destination_buffer, source_buffer, len(message))

# Convert destination buffer to string and print
print(destination_buffer.value.decode('utf-8'))