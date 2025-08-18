import ctypes

def copy_memory(destination, source, num_bytes):
    ctypes.memmove(destination, source, num_bytes)

source_string = b"Hello"
destination_buffer = ctypes.create_string_buffer(len(source_string))

copy_memory(ctypes.addressof(destination_buffer), source_string, len(source_string))