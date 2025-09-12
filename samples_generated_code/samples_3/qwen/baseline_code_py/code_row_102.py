import ctypes

def memcpy(dest, src, n):
    ctypes.memmove(ctypes.c_char_p(dest), ctypes.c_char_p(src), n)

# Example usage
source_message = b"Hello, World!"
buffer = (ctypes.c_char * len(source_message))()

memcpy(buffer, source_message, len(source_message))

print(buffer.value)