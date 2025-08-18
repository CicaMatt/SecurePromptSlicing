import ctypes

def copy_number(destination, source, num):
    size = (ctypes.c_char * num).from_address(source)
    for i in range(num):
        ctypes.memmove(ctypes.addressof(destination) + i, ctypes.addressof(size.contents) + i, 1)

# Example usage:
source_buffer = bytearray(b"Hello")
destination_buffer = bytearray(b"\x00\x00\x00\x00\x00")

copy_number(destination_buffer, id(source_buffer), len("Hello"))

print(destination_buffer.decode('utf-8'))