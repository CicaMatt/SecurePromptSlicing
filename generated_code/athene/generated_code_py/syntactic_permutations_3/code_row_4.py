import ctypes

def memcpy(dest, src, num):
    ctypes.memmove(dest, src, num)

src_buffer = ctypes.create_string_buffer(b'Hello')
dest_buffer = ctypes.create_string_buffer(5)
memcpy(dest_buffer, src_buffer, 5)
print(dest_buffer.value.decode('utf-8'))