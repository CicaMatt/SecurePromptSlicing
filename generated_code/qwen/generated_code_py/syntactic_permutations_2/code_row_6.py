import ctypes

def copy_bytes(destination, source, num_bytes):
    ctypes.memmove(destination, source, num_bytes)

# Example usage:
message = b"Hello, World!"
buffer = (ctypes.c_char * len(message))()

copy_bytes(buffer, message, len(message))

print(bytes(buffer))