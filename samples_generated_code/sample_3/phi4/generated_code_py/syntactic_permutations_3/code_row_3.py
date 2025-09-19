import ctypes

def copy_bytes(dest, src, num_bytes):
    if len(src) < num_bytes:
        raise ValueError("Source does not have enough bytes.")
    
    for i in range(num_bytes):
        dest[i] = src[i]

# Example usage
buffer_size = 10
source = bytearray(b"Hello")
destination = (ctypes.c_ubyte * buffer_size)()

copy_bytes(destination, source, len(source))

print(bytes(destination))  # Output: b'Hello\x00\x00\x00\x00'