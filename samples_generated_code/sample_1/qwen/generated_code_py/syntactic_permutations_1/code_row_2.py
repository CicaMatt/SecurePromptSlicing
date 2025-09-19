import ctypes

def memcpy(dest, src, num_bytes):
    ctypes.memmove(ctypes.c_void_p(dest), ctypes.c_void_p(src), num_bytes)

# Example usage:
if __name__ == "__main__":
    source = bytearray(b"Hello, World!")
    destination = bytearray(len(source))

    memcpy(ctypes.addressof(destination), ctypes.addressof(source), len(source))
    
    print(bytes(destination))