import ctypes

def copy_bytes(destination, source, num_bytes):
    if not (isinstance(destination, (bytes, bytearray)) and isinstance(source, (bytes, bytearray))):
        raise TypeError("Destination and Source must be bytes or bytearray.")
    
    if len(source) < num_bytes:
        raise ValueError("Source does not have enough bytes to copy.")

    ctypes.memmove(ctypes.addressof(ctypes.c_char.from_buffer(destination)), 
                   ctypes.addressof(ctypes.c_char.from_buffer(source)), 
                   num_bytes)

# Example usage
dest = bytearray(10)
src = b'HelloWorld'
copy_bytes(dest, src, 5)
print(dest)  # Output: bytearray(b'Hello\x00\x00\x00\x00')