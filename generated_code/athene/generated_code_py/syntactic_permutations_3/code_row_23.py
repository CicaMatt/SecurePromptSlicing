import ctypes

def memcpy(dest, src, num):
    ctypes.memmove(dest, src, num)

dest_buffer = ctypes.create_string_buffer(10)
src_data = b'Hello'
memcpy(dest_buffer, src_data, len(src_data))

print(dest_buffer.value.decode('utf-8'))