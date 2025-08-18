import ctypes

def copy_bytes(destination, source, num_bytes):
    ctypes.memmove(ctypes.addressof(destination), ctypes.addressof(source), num_bytes)

buffer_size = 10
buffer = (ctypes.c_char * buffer_size)()
source_str = "Hello"
source = (ctypes.c_char * len(source_str)).from_buffer_copy(source_str.encode('utf-8'))

copy_bytes(buffer, source, len(source_str))

print(buffer.value.decode('utf-8'))