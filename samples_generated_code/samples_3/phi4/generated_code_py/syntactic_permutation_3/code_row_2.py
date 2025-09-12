import ctypes

def memcpy(dest, src, num_bytes):
    if len(src) < num_bytes:
        raise ValueError("Source does not have enough bytes to copy.")
    for i in range(num_bytes):
        dest[i] = src[i]

src_string = b"Hello"
num_bytes_to_copy = 5
buffer_size = 10

# Create buffers with ctypes
src_buffer = (ctypes.c_char * len(src_string)).from_buffer_copy(src_string)
dest_buffer = (ctypes.c_char * buffer_size)()

# Copy data from src_buffer to dest_buffer
memcpy(dest_buffer, src_buffer, num_bytes_to_copy)

# Output the result for verification
print("Destination Buffer:", bytes(dest_buffer))