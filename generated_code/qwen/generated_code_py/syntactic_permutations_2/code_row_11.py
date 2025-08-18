import ctypes

def copy_memory(destination, source, num_bytes):
    ctypes.memmove(destination, source, num_bytes)

# Example usage:
message = b"Hello, World!"
buffer = (ctypes.c_char * len(message))()

copy_memory(buffer, message, len(message))

print(buffer.value)