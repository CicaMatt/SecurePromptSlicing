from ctypes import *

def scan(format):
    buffer = create_string_buffer(1024)
    scanf(format, buffer)
    return buffer.value