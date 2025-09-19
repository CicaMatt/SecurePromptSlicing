import ctypes

def memcopy(dest, src, num_bytes):
    ctypes.memmove(dest, src, num_bytes)

src_buffer = ctypes.create_string_buffer(b'Hello')
dest_buffer = ctypes.create_string_buffer(5)
memcopy(dest_buffer, src_buffer, 5)

print(dest_buffer.value.decode('utf-8'))