import ctypes

def memcpy(dest, src, num_bytes):
    if not isinstance(dest, (bytes, bytearray)) or not isinstance(src, (bytes, bytearray)):
        raise TypeError("Both source and destination must be bytes-like objects.")
    if len(src) < num_bytes:
        raise ValueError("Source is shorter than the number of bytes to copy.")
    
    ctypes.memmove(ctypes.addressof(ctypes.create_string_buffer(dest)), 
                   ctypes.addressof(ctypes.create_string_buffer(src, num_bytes)), 
                   num_bytes)

# Example usage
buffer = bytearray(10)
message = b"hello"
memcpy(buffer, message, 5)
print(buffer)  # Output: bytearray(b'hello\x00\x00\x00\x00')