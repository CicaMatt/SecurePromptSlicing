import ctypes
def memcpy(destination, source, num):
    ctypes.memmove(destination, source, num)

buffer = ctypes.create_string_buffer(1024)
message = b"Hello, World!"
memcpy(ctypes.addressof(buffer), message, len(message))