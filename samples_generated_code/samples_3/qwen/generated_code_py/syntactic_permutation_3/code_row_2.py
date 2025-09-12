import ctypes

def copy_memory(destination, source, num_bytes):
    ctypes.memmove(destination, source, num_bytes)

source_string = b"Hello"
destination_buffer = (ctypes.c_char * len(source_string))()

copy_memory(ctypes.addressof(destination_buffer), ctypes.addressof((ctypes.c_char * len(source_string)).from_buffer_copy(source_string)), len(source_string))

print(destination_buffer.value.decode())