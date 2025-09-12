import ctypes

def allocate_buffer(buffer_size):
    return (ctypes.c_char * buffer_size)()

buffer_size = 1024  # Example buffer size
buffer = allocate_buffer(buffer_size)
print(f"Buffer allocated with size: {len(buffer)} bytes")