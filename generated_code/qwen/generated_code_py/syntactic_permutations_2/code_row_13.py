import ctypes

def copy_memory(destination, source, num_bytes):
    ctypes.memmove(destination, source, num_bytes)

# Example usage:
source_buffer = (ctypes.c_char * 10).from_buffer_copy(b"HelloWorld")
destination_buffer = (ctypes.c_char * 10)()

copy_memory(ctypes.addressof(destination_buffer), ctypes.addressof(source_buffer), 5)

print(bytes(destination_buffer))  # Output: b'Hello'