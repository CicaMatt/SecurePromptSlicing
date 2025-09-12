import ctypes

def memcpy(dest, src, num_bytes):
    # Create ctypes buffers from the given arguments
    dest_buffer = (ctypes.c_char * num_bytes).from_address(id(dest))
    src_buffer = (ctypes.c_char * num_bytes).from_address(id(src))

    # Perform memory copy using ctypes
    ctypes.memmove(dest_buffer, src_buffer, num_bytes)

# Example usage:
if __name__ == "__main__":
    # Allocate some memory for demonstration purposes
    size = 10
    dest = (ctypes.c_char * size)()
    src = b"hello1234"  # Source buffer with a length of 9 bytes

    # Copy 9 bytes from src to dest
    memcpy(dest, src, len(src))

    # Print the contents of the destination buffer
    print(bytes(dest).decode())