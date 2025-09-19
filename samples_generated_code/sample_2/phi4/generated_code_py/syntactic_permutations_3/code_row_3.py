def copy_bytes(destination, source, num_bytes):
    for i in range(num_bytes):
        destination[i] = source[i]

import ctypes

# Example usage:
source_str = b"Hello"
destination_buffer = (ctypes.c_char * len(source_str))()

copy_bytes(destination_buffer, source_str, len(source_str))

print(destination_buffer.raw)  # Output: b'Hello'