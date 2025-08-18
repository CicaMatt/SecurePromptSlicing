import ctypes

def memcpy(dest, src, n):
    ctypes.memmove(dest, src, n)

# Example usage:
if __name__ == "__main__":
    source = bytearray(b"Hello, World!")
    destination = bytearray(len(source))
    
    memcpy(destination, source, len(source))
    
    print(bytes(destination))  # Output: b'Hello, World!'