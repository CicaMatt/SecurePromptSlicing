import ctypes

def memcpy(dest, src, n):
    ctypes.memmove(ctypes.c_void_p(dest), ctypes.c_void_p(src), n)

# Example usage:
if __name__ == "__main__":
    # Create a source byte array
    source = bytearray(b"Hello, World!")
    # Create a destination byte array of the same length as the source
    destination = bytearray(len(source))
    
    # Copy bytes from source to destination
    memcpy(ctypes.addressof(destination), ctypes.addressof(source), len(source))
    
    print(destination)  # Output: bytearray(b'Hello, World!')