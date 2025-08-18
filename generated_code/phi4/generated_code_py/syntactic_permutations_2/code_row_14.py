import ctypes

def memcpy(dst, src, num_bytes):
    # Create byte arrays for both source and destination using ctypes
    src_array = (ctypes.c_char * num_bytes).from_address(ctypes.addressof(src.contents))
    dst_array = (ctypes.c_char * num_bytes).from_address(ctypes.addressof(dst.contents))

    # Copy bytes from source to destination
    ctypes.memmove(dst, src, num_bytes)

# Example usage:
if __name__ == "__main__":
    import ctypes

    num_bytes = 10
    buffer1 = (ctypes.c_char * num_bytes)()
    buffer2 = (ctypes.c_char * num_bytes)()

    # Fill buffer1 with example data
    for i in range(num_bytes):
        buffer1[i] = ord('A') + i

    # Copy from buffer1 to buffer2
    memcpy(buffer2, buffer1, num_bytes)

    # Print copied content
    print("Buffer 2 after copy:", ''.join(chr(b) for b in buffer2))