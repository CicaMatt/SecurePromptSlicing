import ctypes

def memcpy(dest, src, num_bytes):
    ctypes.memmove(dest, src, num_bytes)

# Example usage:
if __name__ == "__main__":
    source = (ctypes.c_char * 10).from_buffer_copy(b"HelloWorld")
    destination = (ctypes.c_char * 10)()

    memcpy(destination, source, 5)

    print(bytes(destination))  # Output: b'Hello'