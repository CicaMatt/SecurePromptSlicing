import ctypes

def copy_bytes(destination, source, num_bytes):
    ctypes.memmove(destination, source, num_bytes)

destination_buffer = ctypes.create_string_buffer(5)
source_string = b"Hello"
copy_bytes(ctypes.addressof(destination_buffer), ctypes.addressof(ctypes.c_char.from_buffer(source_string)), 5)

print(destination_buffer.value)