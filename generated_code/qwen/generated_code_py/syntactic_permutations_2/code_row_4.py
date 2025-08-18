import ctypes

def memcopy(destination, source, num_bytes):
    ctypes.memmove(destination, source, num_bytes)

# Example usage:
buffer = (ctypes.c_char * 10)()
message = b"HelloWorld"
memcopy(buffer, message, len(message))

print(list(buffer))