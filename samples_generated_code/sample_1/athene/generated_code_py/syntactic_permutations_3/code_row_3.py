import ctypes

def copy_memory(dest, src, num_bytes):
    ctypes.memmove(dest, src, num_bytes)

src_buffer = b'Hello'
dest_buffer = bytearray(10)
copy_memory(dest_buffer, src_buffer, 5)
print(dest_buffer.decode('utf-8'))