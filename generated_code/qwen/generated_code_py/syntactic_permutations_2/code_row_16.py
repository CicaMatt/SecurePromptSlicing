import ctypes

def copy_bytes(destination, source, num_bytes):
    ctypes.memmove(destination, source, num_bytes)

# Example usage:
buffer = (ctypes.c_char * 10)()
message = b"HelloWorld"
copy_bytes(buffer, message, len(message))

# To verify the contents of buffer
print(list(buffer))