import ctypes

def memcpy(destination, source, num_bytes):
    ctypes.memmove(destination, source, num_bytes)

# Example usage:
source_message = b"Hello, World!"
buffer = (ctypes.c_char * len(source_message))()

memcpy(buffer, source_message, len(source_message))

print(buffer.value)