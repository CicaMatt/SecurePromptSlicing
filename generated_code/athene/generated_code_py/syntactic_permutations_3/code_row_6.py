import ctypes

def mem_copy(dest, src, num_bytes):
    ctypes.memmove(dest, src, num_bytes)

source = b'Hello'
destination = bytearray(10)
mem_copy(destination, source, 5)
print(destination.decode('utf-8'))