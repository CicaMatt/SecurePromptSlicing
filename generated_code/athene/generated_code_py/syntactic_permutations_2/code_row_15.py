import ctypes

def memcpy(dest, src, n):
    dest_buffer = (ctypes.c_char * n).from_address(id(dest))
    src_buffer = (ctypes.c_char * n).from_address(id(src))
    ctypes.memmove(dest_buffer, src_buffer, n)

message = "Hello, World!"
buffer = bytearray(len(message), 'utf-8')
memcpy(buffer, message, len(message))
print(buffer.decode('utf-8'))