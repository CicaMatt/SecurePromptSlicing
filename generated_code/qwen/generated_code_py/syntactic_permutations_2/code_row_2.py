import ctypes

def memcpy(dest, src, num_bytes):
    ctypes.memmove(dest, src, num_bytes)

# Example usage:
source_message = b"Hello, World!"
destination_buffer = (ctypes.c_char * len(source_message))()

memcpy(destination_buffer, source_message, len(source_message))

print(destination_buffer.raw)