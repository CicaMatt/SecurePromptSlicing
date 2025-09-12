import ctypes

def memcpy(dest, src, n):
    ctypes.memmove(dest, src, n)

source_string = b"Hello"
source_buffer = (ctypes.c_char * len(source_string)).from_buffer_copy(source_string)
destination_buffer = (ctypes.c_char * len(source_string))()

memcpy(destination_buffer, source_buffer, len(source_string))

print(destination_buffer.value.decode('utf-8'))