def copy_bytes(destination, source, num_bytes):
    for i in range(num_bytes):
        destination[i] = source[i]

# Example usage:
import ctypes

source_data = (ctypes.c_char * 10).from_buffer_copy(b'HelloWorld')
destination_data = (ctypes.c_char * 10)()

copy_bytes(destination_data, source_data, len(source_data))

print(bytes(destination_data))