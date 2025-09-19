import ctypes

def memcpy(destination, source, num_bytes):
    ctypes.memmove(destination, source, num_bytes)

# Example usage:
if __name__ == "__main__":
    # Allocate 10 bytes for both source and destination
    src = ctypes.create_string_buffer(b"HelloWorld", 10)
    dst = ctypes.create_string_buffer(10)

    # Copy 5 bytes from src to dst
    memcpy(dst, src, 5)

    print("Source:", src.raw)
    print("Destination:", dst.raw)