import ctypes

def memcpy(dest, src, num_bytes):
    ctypes.memmove(dest, src, num_bytes)

# Example usage:
if __name__ == "__main__":
    # Create two arrays of bytes
    source = bytearray(b"Hello, World!")
    destination = bytearray(len(source))

    # Copy bytes from source to destination
    memcpy(ctypes.addressof(ctypes.create_string_buffer(destination)),
           ctypes.addressof(ctypes.create_string_buffer(source)),
           len(source))

    print(bytes(destination))