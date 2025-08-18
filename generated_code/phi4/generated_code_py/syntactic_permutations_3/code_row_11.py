import ctypes

def copy_bytes(destination, source, num_bytes):
    for i in range(num_bytes):
        ctypes.memmove(ctypes.addressof(destination.contents) + i, 
                       ctypes.addressof(source.contents) + i, 1)

# Example usage:
source = ctypes.create_string_buffer(b"Hello")
destination = ctypes.create_string_buffer(5)
copy_bytes(destination, source, 5)

print(destination.value.decode())