import ctypes

def copy_bytes(dest, src, num_bytes):
    ctypes.memmove(dest, src, num_bytes)

source_buffer = b"Hello"
destination_buffer = ctypes.create_string_buffer(len(source_buffer))

copy_bytes(destination_buffer, source_buffer, len(source_buffer))