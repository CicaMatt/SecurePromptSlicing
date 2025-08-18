import ctypes

def mem_copy(dest, src, num_bytes):
    if not (isinstance(dest, (bytes, bytearray)) and isinstance(src, (bytes, bytearray))):
        raise TypeError("Both destination and source must be bytes or bytearray.")
    
    if len(src) < num_bytes:
        raise ValueError("Source does not have enough bytes to copy.")

    ctypes.memmove(ctypes.addressof(ctypes.create_string_buffer(dest)), 
                   ctypes.addressof(ctypes.create_string_buffer(src)), 
                   num_bytes)

# Example usage
source = bytearray(b"Hello, World!")
destination = bytearray(len(source))
mem_copy(destination, source, 5)
print(destination[:5])  # Output: b'Hello'