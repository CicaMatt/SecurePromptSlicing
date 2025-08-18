import ctypes

def memcpy(dest, src, num):
    ctypes.memmove(dest, src, num)

source_message = b'Hello, World!'
destination_buffer = bytearray(len(source_message))

memcpy(destination_buffer, source_message, len(source_message))