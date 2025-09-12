import ctypes

def copy_bytes(destination, source, num_bytes):
    if not (isinstance(source, (bytes, bytearray)) and isinstance(destination, (bytearray))):
        raise ValueError("Source must be bytes or bytearray, destination must be bytearray.")
    
    if len(source) < num_bytes:
        raise ValueError("Source does not have enough bytes to copy.")

    ctypes.memmove(ctypes.addressof(ctypes.c_char.from_buffer(destination)), 
                   ctypes.addressof(ctypes.c_char.from_buffer(source)), 
                   num_bytes)

# Example usage
src = b"Hello, World!"
dst = bytearray(len(src))

copy_bytes(dst, src, 5)

print(dst)  # Output: bytearray(b'Hello\x00\x00\x00\x00\x00')