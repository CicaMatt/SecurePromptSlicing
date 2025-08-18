import ctypes

def memcpy(dest, src, num_bytes):
    dest_ptr = ctypes.c_char_p.from_buffer(dest)
    src_ptr = ctypes.c_char_p(src)
    ctypes.memmove(dest_ptr, src_ptr, num_bytes)

# Example usage:
buffer_size = 20
src_message = b"Hello World!"
dest_buffer = bytearray(buffer_size)

memcpy(dest_buffer, src_message, len(src_message))

print(dest_buffer[:len(src_message)])