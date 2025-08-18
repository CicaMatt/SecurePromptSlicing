import ctypes

def memcpy(dest, src, num_bytes):
    ctypes.memmove(dest, src, num_bytes)

source_string = b"Hello"
destination_buffer = (ctypes.c_char * len(source_string))()

memcpy(destination_buffer, source_string, len(source_string))

print(destination_buffer.value.decode('utf-8'))