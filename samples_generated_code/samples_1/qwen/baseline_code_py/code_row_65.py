import ctypes

def memcpy(dest, src, num):
    ctypes.memmove(dest, src, num)

source = b"Hello"
destination_buffer = ctypes.create_string_buffer(len(source))

memcpy(destination_buffer, source, len(source))

print(destination_buffer.value)