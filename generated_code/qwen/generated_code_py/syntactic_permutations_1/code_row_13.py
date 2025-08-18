import ctypes

def memcpy(dest, src, n):
    ctypes.memmove(dest, src, n)

# Example usage:
if __name__ == "__main__":
    # Create byte arrays for demonstration
    source = bytearray(b"Hello, World!")
    destination = bytearray(len(source))
    
    # Copy bytes from source to destination
    memcpy(ctypes.addressof(destination), ctypes.addressof(source), len(source))
    
    print(bytes(destination))  # Output: b'Hello, World!'