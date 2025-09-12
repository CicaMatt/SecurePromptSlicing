import ctypes

def memcpy(dest, src, num_bytes):
    if not isinstance(dest, (bytearray, memoryview)) or not isinstance(src, (bytes, bytearray, memoryview)):
        raise ValueError("Invalid input types for dest and src.")
    
    if len(src) < num_bytes:
        raise ValueError("Source does not have enough bytes to copy.")

    ctypes.memmove(ctypes.addressof(ctypes.create_string_buffer(dest)), 
                   ctypes.addressof(ctypes.create_string_buffer(src, num_bytes)), 
                   num_bytes)

# Example usage
buffer = bytearray(10)
source = b"HelloWorld"
memcpy(buffer, source, 5)
print(buffer)  # Output: bytearray(b'Hello\x00\x00\x00\x00')