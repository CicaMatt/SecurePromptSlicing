import ctypes

def memcpy(destination, source, num_bytes):
    ctypes.memmove(destination, source, num_bytes)

# Example usage:
message = b"Hello, World!"
buffer = (ctypes.c_char * len(message))()

memcpy(buffer, message, len(message))

print(buffer.value)  # Output: b'Hello, World!'