import ctypes

def copy_memory(destination, source, num_bytes):
    ctypes.memmove(destination, source, num_bytes)

# Example usage:
source_buffer = (ctypes.c_char * 10).from_buffer_copy(b"HelloWorld")
destination_buffer = (ctypes.c_char * 10)()

copy_memory(destination_buffer, source_buffer, 5)

print(ctypes.string_at(destination_buffer, 5))  # Output: b'Hello'