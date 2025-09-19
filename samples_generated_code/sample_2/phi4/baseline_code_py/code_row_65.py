import ctypes

def copy_bytes(dest, src, num_bytes):
    if len(src) < num_bytes:
        raise ValueError("Source does not contain enough bytes")
    
    for i in range(num_bytes):
        ctypes.memmove(ctypes.addressof(dest[i]), ctypes.addressof(src[i]), 1)

buffer = (ctypes.c_char * 5)()
source = b"Hello"
copy_bytes(buffer, source, 5)

print(buffer[:])  # Output: bytearray(b'Hello')