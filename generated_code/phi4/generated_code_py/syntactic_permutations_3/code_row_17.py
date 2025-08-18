import ctypes

def mem_copy(destination, num_bytes):
    source = b"Hello"
    if len(source) > num_bytes:
        source = source[:num_bytes]
    
    for i in range(len(source)):
        destination[i] = source[i]

# Usage example
buffer_size = 10
destination_buffer = (ctypes.c_char * buffer_size)()
mem_copy(destination_buffer, 5)

# Print the result
print(buffer_size)
for byte in destination_buffer:
    print(byte.decode('utf-8'), end='')