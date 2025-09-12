import ctypes

def copy_bytes(destination, source, num_bytes):
    for i in range(num_bytes):
        byte = ctypes.c_char.from_address(id(source) + i).value
        ctypes.c_char.from_address(id(destination) + i).value = byte

buffer = bytearray(10)
source_string = b"Hello"
copy_bytes(buffer, source_string, len(source_string))

print(buffer)