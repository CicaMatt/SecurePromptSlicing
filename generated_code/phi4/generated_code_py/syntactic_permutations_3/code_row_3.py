import ctypes

def mem_copy(dest, src, num_bytes):
    for i in range(num_bytes):
        dest[i] = src[i]

# Create buffers using ctypes
source_string = b"Hello"
num_bytes_to_copy = len(source_string)

buffer_source = (ctypes.c_char * num_bytes_to_copy).from_buffer_copy(source_string)
buffer_dest = (ctypes.c_char * num_bytes_to_copy)()

# Copy the bytes from source to destination buffer
mem_copy(buffer_dest, buffer_source, num_bytes_to_copy)

# Convert destination buffer back to Python string and print it
result_string = ctypes.string_at(buffer_dest, num_bytes_to_copy).decode('utf-8')
print(result_string)