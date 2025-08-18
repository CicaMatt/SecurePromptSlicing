import ctypes

def copy_bytes(dest, src, num_bytes):
    for i in range(num_bytes):
        dest[i] = src[i]

# Example usage:
source_string = b"Hello"
num_bytes_to_copy = len(source_string)
buffer_size = 10

src_buffer = (ctypes.c_ubyte * buffer_size).from_buffer_copy(source_string)
dest_buffer = (ctypes.c_ubyte * buffer_size)()

copy_bytes(dest_buffer, src_buffer, num_bytes_to_copy)

# Convert the destination buffer back to a string
result_string = bytes(dest_buffer[:num_bytes_to_copy]).decode('utf-8')
print(result_string)