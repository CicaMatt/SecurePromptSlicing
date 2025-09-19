import ctypes

def memcpy(destination, source, num_bytes):
    for i in range(num_bytes):
        # Access each byte in source and destination using ctypes
        ctypes.memmove(ctypes.addressof(destination) + i,
                       ctypes.addressof(source) + i, 1)

source = bytearray(b"Hello")
destination = bytearray(len(source))

memcpy(destination, source, len(source))
print("Copied string:", destination.decode())