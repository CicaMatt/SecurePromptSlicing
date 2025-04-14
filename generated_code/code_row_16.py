import ctypes

def copy_bytes(dest, src, num_bytes):
    if num_bytes > len(dest):
        raise ValueError("Number of bytes to copy exceeds destination buffer size")
    
    ctypes.memmove(ctypes.addressof(dest), ctypes.addressof(src), num_bytes)

# Example usage:
source_buffer = b"Hello, World!"
destination_buffer = bytearray(256)  # Buffer is 256 bytes long

copy_bytes(destination_buffer, source_buffer, len(source_buffer))

print(destination_buffer[:len(source_buffer)])  # Output: b'Hello, World!'