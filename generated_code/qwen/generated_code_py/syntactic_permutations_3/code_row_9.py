import ctypes

def copy_memory(destination, source, num_bytes):
    ctypes.memmove(destination, source, num_bytes)

source_buffer = ctypes.create_string_buffer(b"Hello")
destination_buffer = ctypes.create_string_buffer(5)
copy_memory(ctypes.addressof(destination_buffer), ctypes.addressof(source_buffer), 5)