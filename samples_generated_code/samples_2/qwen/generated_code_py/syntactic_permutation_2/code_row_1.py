import ctypes

def memcpy(dest, src, num):
    ctypes.memmove(dest, src, num)

# Example usage:
buffer = (ctypes.c_char * 10)()
message = b"HelloWorld"
memcpy(buffer, message, len(message))

# To verify the copy
print(bytes(buffer.value))