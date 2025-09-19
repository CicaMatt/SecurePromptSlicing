import ctypes

def memcpy(dest, src, num):
    ctypes.memmove(dest, src, num)

# Example usage:
source_buffer = (ctypes.c_char * 10).from_buffer_copy(b"HelloWorld")
destination_buffer = (ctypes.c_char * 10)()

memcpy(destination_buffer, source_buffer, 10)

print(bytes(destination_buffer))